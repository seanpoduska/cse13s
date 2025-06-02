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
  UNUSED(s);
}

bool startswith(char *longstring, char *prefix) {
  // YOUR CODE HERE
  UNUSED(longstring);
  UNUSED(prefix);
  return false;
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
  UNUSED(table);
}

void store_metadata(MetadataLookupTable *table, PostMetadata *metadata) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(metadata);
}

PostMetadata *metadata_lookup(MetadataLookupTable *table, char *message_id) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(message_id);
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
  UNUSED(table);
}

string_set *term_lookup(TermLookupTable *table, char *term) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(term);
  return NULL;
}

string_set *union_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(queries);
  return NULL;
}

string_set *intersection_lookup(TermLookupTable *table, ll_string *queries) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(queries);
  return NULL;
}

void add_message_id_to_term(TermLookupTable *table, char *term,
                            char *message_id) {
  // YOUR CODE HERE
  UNUSED(table);
  UNUSED(term);
  UNUSED(message_id);
}
