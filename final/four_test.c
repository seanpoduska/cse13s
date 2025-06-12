#include "final.h"

#include <stdio.h>
#include <stdlib.h>

BinaryTree *build_tree(int value, BinaryTree *left, BinaryTree *right) {
  BinaryTree *out = calloc(1, sizeof(BinaryTree));
  out->val = value;
  out->left = left;
  out->right = right;

  return out;
}

void should_be_exactly_equal(const char *message, int expected, int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {
  BinaryTree *tree = build_tree(
      1, build_tree(2, build_tree(4, build_tree(8, NULL, NULL), NULL), NULL),
      build_tree(3, build_tree(5, build_tree(7, NULL, NULL), NULL),
                 build_tree(6, NULL, NULL)));

  // Here we should find 42 at depth 2 (path is 14->15->42)
  should_be_exactly_equal("8 and 7 at max depth", 15,
                          sum_values_at_max_depth(tree));

  return 0;
}
