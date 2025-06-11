#include "index_lib.h"
#include "string_list.h"
#include "string_set.h"

#include <ctype.h>
#include <glob.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Thank you Dan Bernstein.
unsigned long djb_hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

// Find the first newline in the input and replace it with \0
void chomp(char *s) {
  for (int i = 0; s[i]; i++) {
    if (s[i] == '\n' || s[i] == '\r') {
      // Check for \r in case we're on Windows or a very old Mac??
      // Look, I won't stop you from doing CSE 13s on a Mac from 2001 or prior.
      s[i] = '\0';
      break;
    }
  }
}

// string utilities
void lowercase(char *s) {
  // YOUR CODE HERE
  for (int i = 0; s[i]; i++) {
    s[i] = tolower((unsigned char)s[i]);
  }
}

bool startswith(char *longstring, char *prefix) {
  // YOUR CODE HERE
  while (*prefix) {
    if (*prefix != *longstring) return false;
    prefix++;
    longstring++;
  }
  return true;
}

PostMetadata *extract_metadata(char *filename) {        // extracts metadata from database file (result)
  FILE *infile;
  infile = fopen(filename, "r");
  if (!infile) {
    fprintf(stderr, "couldn't open file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  PostMetadata *result = calloc(1, sizeof(PostMetadata));
  char buf[1024];

  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    if (startswith(buf, "From: ") && !result->author) {
      result->author = strdup(buf + strlen("From: "));
    } else if (startswith(buf, "Subject: ") && !result->subject) {
      result->subject = strdup(buf + strlen("Subject: "));
    } else if (startswith(buf, "Message-ID: ") && !result->message_id) {
      result->message_id = strdup(buf + strlen("Message-ID: "));
    } else if (startswith(buf, "Newsgroups: ") && !result->newsgroups) {
      result->newsgroups = strdup(buf + strlen("Newsgroups: "));
    }
  }
  result->filename = strdup(filename);

  fclose(infile);
  return result;
}

static const char *const wordpat = "[0-9a-z']+";
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

ll_string *tokenize_string(char *s) {
  char tokenbuf[200];
  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t len;

  if (regcomp(&regex, wordpat, REG_EXTENDED | REG_NEWLINE | REG_ICASE)) {
    fprintf(stderr, "could not compile the regular expression??\n");
    exit(EXIT_FAILURE);
  }

  ll_string *out = NULL;
  while (true) {
    if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0)) {
      break;
    }
    len = pmatch[0].rm_eo - pmatch[0].rm_so;
    sprintf(tokenbuf, "%.*s", len, s + pmatch[0].rm_so);
    out = append(out, tokenbuf);
    s += pmatch[0].rm_eo;
  }

  regfree(&regex);
  return out;
}

ll_string *extract_terms(char *filename, string_set *stopwords) {
  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t len;
  char linebuf[1024];
  char tokenbuf[200];

  if (regcomp(&regex, wordpat, REG_EXTENDED | REG_NEWLINE | REG_ICASE)) {
    fprintf(stderr, "could not compile the regular expression??\n");
    exit(EXIT_FAILURE);
  }

  FILE *infile = fopen(filename, "r");
  ll_string *out = NULL;

  bool started = false;
  while (fgets(linebuf, 1024, infile)) {
    chomp(linebuf);
    lowercase(linebuf);
    if (!strcmp(linebuf, "")) {
      started = true;
    }
    if (!started) {
      continue;
    }

    char *s = linebuf;
    while (true) {
      if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0)) {
        break;
      }
      len = pmatch[0].rm_eo - pmatch[0].rm_so;
      sprintf(tokenbuf, "%.*s", len, s + pmatch[0].rm_so);
      if (!contains(stopwords, tokenbuf)) {
        out = cons(tokenbuf, out);
      }
      s += pmatch[0].rm_eo;
    }
  }

  regfree(&regex);
  fclose(infile);
  return out;
}

MetadataLookupTable *build_metadata_lookup_table(size_t num_buckets) {
  MetadataLookupTable *out = calloc(1, sizeof(MetadataLookupTable));
  out->num_buckets = num_buckets;

  out->buckets = calloc(num_buckets, sizeof(MetadataLookupList *));

  return out;
}

void free_post_metadata(PostMetadata *metadata) {
  free(metadata->author);
  free(metadata->subject);
  free(metadata->message_id);
  free(metadata->newsgroups);
  free(metadata->filename);
  free(metadata);
}

void free_metadata_lookup_table(MetadataLookupTable *table) {
  // YOUR CODE HERE
  for (size_t i = 0; i < table->num_buckets; i++) {
    MetadataLookupList *node = table->buckets[i];
    while (node) {
      MetadataLookupList *next = node->next;

      free(node->message_id);                 // Free message_id string
      free_post_metadata(node->metadata);     // Free PostMetadata struct
      free(node);                             // Free the linked list node

      node = next;                            // Move to next node
    }
  }

  free(table->buckets);  // Free array of buckets
  free(table);           // Free the table structure itself
}

void store_metadata(MetadataLookupTable *table, PostMetadata *metadata) {
  // YOUR CODE HERE
  if (!metadata || !metadata->message_id) return;

  unsigned long hash = djb_hash(metadata->message_id) % table->num_buckets;

  MetadataLookupList *new_node = calloc(1, sizeof(MetadataLookupList));
  new_node->message_id = strdup(metadata->message_id);
  new_node->metadata = metadata;
  new_node->next = table->buckets[hash];
  table->buckets[hash] = new_node;
}

PostMetadata *metadata_lookup(MetadataLookupTable *table, char *message_id) {
  // YOUR CODE HERE
  unsigned long hash = djb_hash(message_id) % table->num_buckets;
  MetadataLookupList *node = table->buckets[hash];
  while (node) {
    if (strcmp(node->message_id, message_id) == 0) {
      return node->metadata;
    }
    node = node->next;
  }
  return NULL;
}

TermLookupTable *build_term_lookup_table(size_t num_buckets) {
  TermLookupTable *out = calloc(1, sizeof(TermLookupTable));
  out->num_buckets = num_buckets;
  out->buckets = calloc(num_buckets, sizeof(TermLookupList *));

  return out;
}

void free_term_lookup_table(TermLookupTable *table) {
  // YOUR CODE HERE
  for (size_t i = 0; i < table->num_buckets; i++) {
    TermLookupList *node = table->buckets[i];
    while (node) {
      TermLookupList *next = node->next;
      free(node->term);
      free_set(node->message_id_set);
      free(node);
      node = next;
    }
  }
  free(table->buckets);
  free(table);
}

string_set *term_lookup(TermLookupTable *table, char *term) {
  // YOUR CODE HERE
  unsigned long hash = djb_hash(term) % table->num_buckets;
  TermLookupList *node = table->buckets[hash];
  while (node) {
    if (strcmp(node->term, term) == 0) return node->message_id_set;
    node = node->next;
  }
  return NULL;
}

string_set *union_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  string_set *result = make_empty_set();
  while (queries) {
    string_set *ids = term_lookup(table, queries->value);
    result = set_union(result, ids);
    queries = queries->next;
  }
  return result;
}

string_set *intersection_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  if (!queries) return make_empty_set();
  string_set *result = term_lookup(table, queries->value);
  queries = queries->next;
  while (queries) {
    string_set *ids = term_lookup(table, queries->value);
    result = set_intersection(result, ids);
    queries = queries->next;
  }
  return result;
}

void add_message_id_to_term(TermLookupTable *table, char *term,
                            char *message_id) {
  // YOUR CODE HERE
  unsigned long hash = djb_hash(term) % table->num_buckets;
  TermLookupList *node = table->buckets[hash];
  while (node) {
    if (strcmp(node->term, term) == 0) {
      node->message_id_set = add(node->message_id_set, message_id);
      return;
    }
    node = node->next;
  }

  TermLookupList *new_node = calloc(1, sizeof(TermLookupList));
  new_node->term = strdup(term);
  new_node->message_id_set = make_empty_set();
  new_node->message_id_set = add(new_node->message_id_set, message_id);
  new_node->next = table->buckets[hash];
  table->buckets[hash] = new_node;
}
