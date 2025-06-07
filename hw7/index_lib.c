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
    s[i] = tolower(s[i]);
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

PostMetadata *extract_metadata(char *filename) {
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
      char *id_start = buf + strlen("Message-ID: ");
      if (strlen(id_start) > 0) {
        result->message_id = strdup(id_start); // <-- This strdup is essential
      }
    } else if (startswith(buf, "Newsgroups: ") && !result->newsgroups) {
      result->newsgroups = strdup(buf + strlen("Newsgroups: "));
    }
  }

  fclose(infile);
  result->filename = strdup(filename);

  // Final check: if message_id is missing or corrupted, abort
  if (!result->message_id || strlen(result->message_id) == 0) {
    free_post_metadata(result);
    return NULL;
  }

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
    MetadataLookupList *entry = table->buckets[i];
    while (entry) {
      MetadataLookupList *next = entry->next;
      free_post_metadata(entry->metadata);
      free(entry);
      entry = next;
    }
  }
  free(table->buckets);
  free(table);
}

void store_metadata(MetadataLookupTable *table, PostMetadata *metadata) {
  // YOUR CODE HERE
  if (!table || !metadata || !metadata->message_id || strlen(metadata->message_id) == 0) return;

  unsigned long hash = djb_hash(metadata->message_id) % table->num_buckets;
  MetadataLookupList *new_entry = malloc(sizeof(MetadataLookupList));
  new_entry->metadata = metadata;
  new_entry->next = table->buckets[hash];
  table->buckets[hash] = new_entry;
}

PostMetadata *metadata_lookup(MetadataLookupTable *table, char *message_id) {
  // YOUR CODE HERE
  if (!table || !message_id) return NULL;

  // Check if message_id is a valid pointer and not garbage
  if ((unsigned long) message_id < 4096 || strnlen(message_id, 1024) == 1024) {
    fprintf(stderr, "Invalid or suspicious message_id pointer: %p\n", (void *)message_id);
    return NULL;
  }

  unsigned long hash = djb_hash(message_id) % table->num_buckets;
  MetadataLookupList *entry = table->buckets[hash];
  while (entry) {
    if (entry->metadata && entry->metadata->message_id &&
        strcmp(entry->metadata->message_id, message_id) == 0) {
      return entry->metadata;
    }
    entry = entry->next;
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
    TermLookupList *entry = table->buckets[i];
    while (entry) {
      TermLookupList *next = entry->next;
      free_set(entry->message_id_set);
      free(entry->term);
      free(entry);
      entry = next;
    }
  }
  free(table->buckets);
  free(table);
}

string_set *term_lookup(TermLookupTable *table, char *term) {
  // YOUR CODE HERE
  unsigned long hash = djb_hash(term) % table->num_buckets;
  TermLookupList *entry = table->buckets[hash];
  while (entry) {
    if (strcmp(entry->term, term) == 0) {
      return entry->message_id_set;
    }
    entry = entry->next;
  }
  return NULL;
}

string_set *union_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  string_set *result = NULL;
  while (queries) {
    string_set *term_set = term_lookup(table, queries->value);
    if (term_set) {
      result = set_union(result, term_set);
    }
    queries = queries->next;
  }
  return result;
}

string_set *intersection_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  string_set *result = NULL;
  while (queries) {
    string_set *term_set = term_lookup(table, queries->value);
    if (!term_set) return NULL;
    if (!result)
      result = set_union(NULL, term_set);  // make a copy
    else {
      string_set *temp = set_intersection(result, term_set);
      free_set(result);
      result = temp;
    }
    queries = queries->next;
  }
  return result;
}

void add_message_id_to_term(TermLookupTable *table, char *term,
                            char *message_id) {
  // YOUR CODE HERE
  unsigned long hash = djb_hash(term) % table->num_buckets;
  TermLookupList *entry = table->buckets[hash];
  while (entry) {
    if (strcmp(entry->term, term) == 0) {
      entry->message_id_set = add(entry->message_id_set, message_id);
      return;
    }
    entry = entry->next;
  }
  TermLookupList *new_entry = malloc(sizeof(TermLookupList));
  new_entry->term = strdup(term);
  new_entry->message_id_set = add(NULL, message_id);
  new_entry->next = table->buckets[hash];
  table->buckets[hash] = new_entry;
}
