#pragma once

#include "string_list.h"
#include "string_set.h"

#include <stdio.h>

typedef struct PostMetadata {
  char *author;
  char *subject;
  char *message_id;
  char *newsgroups;
  char *filename;
} PostMetadata;

ll_string *extract_terms(char *filename, string_set *stopwords);

PostMetadata *extract_metadata(char *filename);
void free_post_metadata(PostMetadata *metadata);

// given postid, lookup its associated metadata
typedef struct MetadataLookupList {
  // key on message_id
  char *message_id;
  PostMetadata *metadata;
  struct MetadataLookupList *next;
} MetadataLookupList;

typedef struct MetadataLookupTable {
  size_t num_buckets;
  struct MetadataLookupList **buckets;
} MetadataLookupTable;

MetadataLookupTable *build_metadata_lookup_table(size_t num_buckets);
PostMetadata *metadata_lookup(MetadataLookupTable *table, char *message_id);
void store_metadata(MetadataLookupTable *table, PostMetadata *metadata);
void free_metadata_lookup_table(MetadataLookupTable *table);

// given a term, look up the set of post IDs for that term
typedef struct TermLookupList {
  char *term;
  string_set *message_id_set;
  struct TermLookupList *next;
} TermLookupList;

typedef struct TermLookupTable {
  size_t num_buckets;
  struct TermLookupList **buckets;
} TermLookupTable;

TermLookupTable *build_term_lookup_table(size_t num_buckets);
string_set *term_lookup(TermLookupTable *table, char *term);
void add_message_id_to_term(TermLookupTable *table, char *term,
                            char *message_id);
void free_term_lookup_table(TermLookupTable *table);

string_set *union_lookup(TermLookupTable *table, ll_string *queries);
string_set *intersection_lookup(TermLookupTable *table, ll_string *queries);

// string utils
bool startswith(char *longstring, char *prefix);
void chomp(char *s);
void lowercase(char *s);

ll_string *tokenize_string(char *s);


// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
