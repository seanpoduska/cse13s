#include "string_set.h"
#include "string_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// given helper function
string_set *make_empty_set(void) { return NULL; }

// added helper function, makes new node
string_set *make_node(char *s) {
  string_set *node = malloc(sizeof(string_set));
  node->s = strdup(s);  // copy string
  node->left = NULL;
  node->right = NULL;
  return node;
}

// added helper to add entries to linked list (in-order traversal)
void to_list(string_set *set, ll_string **list) {
  if (set == NULL) return;
  to_list(set->left, list);
  ll_string *new_node = malloc(sizeof(ll_string));
  new_node->s = strdup(set->s);
  new_node->next = *list;
  *list = new_node;
  to_list(set->right, list);
}

// Helper to copy all strings from one set into another
string_set *copy_all(string_set *dest, string_set *src) {
  if (src == NULL) return dest;
  dest = copy_all(dest, src->left);
  dest = add(dest, src->s);
  dest = copy_all(dest, src->right);
  return dest;
}

// Helper to copy strings from A that are also in B
string_set *copy_if_in_b(string_set *result, string_set *a, string_set *b) {
  if (a == NULL) return result;
  result = copy_if_in_b(result, a->left, b);
  if (contains(b, a->s)) {
    result = add(result, a->s);
  }
  result = copy_if_in_b(result, a->right, b);
  return result;
}

// ---------- main functions below ----------

bool contains(string_set *set, char *s) {
  // YOUR CODE HERE
  if (set == NULL) return false;
  int cmp = strcmp(s, set->s);
  if (cmp == 0) return true;
  if (cmp < 0)
    return contains(set->left, s);
  else
    return contains(set->right, s);
}

string_set *add(string_set *set, char *s) {
  // YOUR CODE HERE
  if (set == NULL) return make_node(s);
  int cmp = strcmp(s, set->s);
  if (cmp == 0) {
    return set;  // already exists
  } else if (cmp < 0) {
    set->left = add(set->left, s);
  } else {
    set->right = add(set->right, s);
  }
  return set;
}

ll_string *list_entries(string_set *set) {
  // YOUR CODE HERE
  ll_string *list = NULL;
  to_list(set, &list);
  return list;
}

string_set *set_union(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  string_set *result = NULL;
  result = copy_all(result, set_a);
  result = copy_all(result, set_b);
  return result;
}

string_set *set_intersection(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  string_set *result = NULL;
  result = copy_if_in_b(result, set_a, set_b);
  return result;
}

void free_set(string_set *set) {
  // YOUR CODE HERE
  if (set == NULL) return;
  free_set(set->left);
  free_set(set->right);
  free(set->s);
  free(set);
}
