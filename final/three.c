#include "final.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// PROBLEM 3

// Thank you Dan Bernstein.
unsigned long hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while (*str != '\0') {
    c = *str;
    hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
    str++;
  }
  return hash;
}

// Construct an empty WordCountTable.
WordCountTable *build_word_count_table(size_t num_buckets) {
  WordCountTable *out;

  out = calloc(1, sizeof(WordCountTable));
  out->num_buckets = num_buckets;

  // bunch of NULL pointers to WordCountNode.
  out->buckets = calloc(num_buckets, sizeof(WordCountNode *));
  return out;
}

// Your code goes in here!
void increment_word_count(char *word, WordCountTable *table) {
  if (!word || !table) return;
  
  char *copy = malloc(strlen(word) + 1);
  if (!copy) return;
  strcpy(copy, word);
  
  for (size_t i = 0; copy[i]; i++) {
    copy[i] = tolower((unsigned char) copy[i]);
  }

  unsigned long h = hash(copy);
  size_t index = h % table->num_buckets;

  WordCountNode *node = table->buckets[index];
  while (node) {
    if (strcmp(node->word, copy) == 0) {
      node->count += 1;
      free(copy);
      return;
    }
    node = node->next;
  }

  WordCountNode *new_node = calloc(1, sizeof(WordCountNode));
  new_node->word = copy;
  new_node->count = 1;
  new_node->next = table->buckets[index];
  table->buckets[index] = new_node;

  // Note that inside the table, all words should be stored in lowercase. For
  // simplicity all words will be sequences of [A-Za-z]. This function may be
  // passed words with capital letters though! So do your conversion here before
  // doing further processing.
}

// Your code goes in here too!
int lookup_word_count(char *word, WordCountTable *table) {
  if (!word || !table) return 0;

  char *copy = malloc(strlen(word) + 1);
  if (!copy) return 0;
  strcpy(copy, word);

  for (size_t i = 0; copy[i]; i++) {
    copy[i] = tolower((unsigned char) copy[i]);
  }

  unsigned long h = hash(copy);
  size_t index = h % table->num_buckets;

  WordCountNode *node = table->buckets[index];
  while (node) {
    if (strcmp(node->word, copy) == 0) {
      free(copy);
      return node->count;
    }
    node = node->next;
  }

  // Note that inside the table, all words should be stored in lowercase. For
  // simplicity all words will be sequences of [A-Za-z]. This function may be
  // passed words with capital letters though! So do your conversion here before
  // doing further processing.
  
  free(copy);
  return 0;
}
