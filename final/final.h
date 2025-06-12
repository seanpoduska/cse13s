#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Question one.
size_t count_increasing_columns(int **matrix, size_t rows, size_t cols);

// Question two.
char *remove_characters(char *text, char *toremove);

// Question three.
unsigned long hash(char *str);

typedef struct WordCountNode {
  char *word;
  int count;
  struct WordCountNode *next;
} WordCountNode;

typedef struct WordCountTable {
  size_t num_buckets;
  WordCountNode **buckets;
} WordCountTable;

WordCountTable *build_word_count_table(size_t num_buckets);
void increment_word_count(char *word, WordCountTable *table);
int lookup_word_count(char *word, WordCountTable *table);

// Question four.
typedef struct BinaryTree {
  int val;
  struct BinaryTree *left;
  struct BinaryTree *right;
} BinaryTree;

int sum_values_at_max_depth(BinaryTree *tree);

// Question five.
typedef struct ll_int {
  int val;
  struct ll_int *next;
} ll_int;

void find_two_lowest(ll_int *linkedlist, int *lowest, int *nextlowest);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
