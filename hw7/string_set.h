#pragma once

#include "string_list.h"
#include <stdbool.h>

typedef struct string_set {
  char *value;
  struct string_set *left;
  struct string_set *right;
} string_set;

string_set *make_empty_set(void);

bool contains(string_set *set, char *s);

string_set *add(string_set *set, char *s);
void set_remove(string_set *set, char *s);
ll_string *list_entries(string_set *set);

string_set *set_union(string_set *set_a, string_set *set_b);
string_set *set_intersection(string_set *set_a, string_set *set_b);

void free_set(string_set *set);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
