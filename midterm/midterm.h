#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Question one.
int array_sort_direction(int *arr, size_t len);

// Question two.
typedef struct ll_float {
  float value;
  struct ll_float *next;
} ll_float;

ll_float *delete_range(ll_float *list, float start, float end);

// Question three.
size_t count_strings_with_property(bool (*property)(char *), char **strings,
                                   size_t len);

// Question four.
size_t *count_characters(char *s, char *count_these, size_t num_characters);

// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
