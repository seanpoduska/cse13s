#include "string_set.h"
#include "string_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_set *make_empty_set(void) { return NULL; }

bool contains(string_set *set, char *value) {
  // YOUR CODE HERE
  if (set == NULL) return false;                         // base case: empty tree
  int cmp = strcmp(value, set->value);
  if (cmp == 0) return true;                            // match found
  else if (cmp < 0) return contains(set->left, value);  // search left
  else return contains(set->right, value);              // search right
}

string_set *add(string_set *set, char *value) {
  // YOUR CODE HERE
  if (set == NULL) {
    string_set *new_node = malloc(sizeof(string_set));  // allocate mem
    new_node->value = strdup(value);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }

  int cmp = strcmp(value, set->value);
  if (cmp == 0) return set;                             // already exists
  else if (cmp < 0) set->left = add(set->left, value);  // insert left
  else set->right = add(set->right, value);             // insert right
  return set;
}

static void in_order_to_list(string_set *set, ll_string **head) {
  if (set == NULL) return;
  in_order_to_list(set->right, head); // Reverse order
  *head = cons(set->value, *head);    // Prepend to list
  in_order_to_list(set->left, head);
}

ll_string *list_entries(string_set *set) {
  // YOUR CODE HERE
  ll_string *list = NULL;
  in_order_to_list(set, &list);
  return list;
}

string_set *set_union(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  if (set_b == NULL) return set_a;        // Nothing to add
  set_a = add(set_a, set_b->value);       // Add root of B
  set_a = set_union(set_a, set_b->left);  // Recurse left
  set_a = set_union(set_a, set_b->right); // Recurse right
  return set_a;
}

string_set *set_intersection(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  if (set_a == NULL) return NULL;

  // Recurse both sides regardless
  string_set *left = set_intersection(set_a->left, set_b);
  string_set *right = set_intersection(set_a->right, set_b);

  if (contains(set_b, set_a->value)) {
    // Create node for intersection match
    string_set *node = malloc(sizeof(string_set));
    node->value = strdup(set_a->value);
    node->left = left;
    node->right = right;
    return node;
  } else {
    // Cleanup partial results and discard
    free_set(left);
    free_set(right);
    return NULL;
  }
}

void free_set(string_set *set) {
  // YOUR CODE HERE
  if (set == NULL) return;
  free_set(set->left);  // Free left subtree
  free_set(set->right); // Free right subtree
  free(set->value);     // Free string
  free(set);            // Free node itself
}
