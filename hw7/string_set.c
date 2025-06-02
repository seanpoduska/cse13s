#include "string_set.h"
#include "string_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string_set *make_empty_set(void) { return NULL; }

bool contains(string_set *set, char *s) {
  // YOUR CODE HERE
  UNUSED(set);
  UNUSED(s);
  return false;
}

string_set *add(string_set *set, char *s) {
  // YOUR CODE HERE
  UNUSED(set);
  UNUSED(s);
  return NULL;
}

ll_string *list_entries(string_set *set) {
  // YOUR CODE HERE
  UNUSED(set);
  return NULL;
}

string_set *set_union(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  UNUSED(set_a);
  UNUSED(set_b);
  return NULL;
}

string_set *set_intersection(string_set *set_a, string_set *set_b) {
  // YOUR CODE HERE
  UNUSED(set_a);
  UNUSED(set_b);
  return NULL;
}

void free_set(string_set *set) {
  // YOUR CODE HERE
  UNUSED(set);
}
