#pragma once

#include <stdio.h>

typedef struct ll_string {
  char *value;
  struct ll_string *next;
} ll_string;

ll_string *cons(char *s, ll_string *list);
ll_string *extend(ll_string *list, ll_string *addthese);
ll_string *append(ll_string *list, char *s);
ll_string *get_element(ll_string *list, size_t i);

void free_list(ll_string *list);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
