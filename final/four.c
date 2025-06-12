#include "final.h"

#include <stdio.h>

int find_max_depth(BinaryTree *node) {
  if (node == NULL) return -1;
  int left_depth = find_max_depth(node->left);
  int right_depth = find_max_depth(node->right);
  return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

int sum_at_depth(BinaryTree *node, int current_depth, int target_depth) {
  if (node == NULL) return 0;
  if (current_depth == target_depth) return node->val;
  return sum_at_depth(node->left, current_depth + 1, target_depth) +
         sum_at_depth(node->right, current_depth + 1, target_depth);
}

int sum_values_at_max_depth(BinaryTree *tree) {
  // Your code here!
  if (tree == NULL) return 0;
  int max_depth = find_max_depth(tree);
  return sum_at_depth(tree, 0, max_depth);
}
