/*
 * All of your code for hw3 goes in here. Your goal is to finish these
 * functions.
 */

#include "hw3.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool str_suffix(char *haystack, char *needle) {
  UNUSED(haystack);
  UNUSED(needle);
  return false;
}

char *str_repeat(char *s, int n) {
  UNUSED(s);
  UNUSED(n);

  char *out = malloc(sizeof(char) * 1);
  out[0] = '\0';

  return out;
}

bool str_is_palindrome(char *s) {
  UNUSED(s);
  return false;
}

float dot_product(float *vec_a, float *vec_b, int length) {
  UNUSED(vec_a);
  UNUSED(vec_b);
  UNUSED(length);
  return 0;
}

int reduce(int *nums, int length, int (*f)(int, int), int initial) {
  UNUSED(nums);
  UNUSED(length);
  UNUSED(f);
  UNUSED(initial);
  return 0;
}

// These two functions will end up as a *single call to reduce*, but you'll have
// to write a new helper function for each of them. Those helper functions will
// be quite short though!

int maximum_with_reduce(int *nums, int length) {
  UNUSED(nums);
  UNUSED(length);
  return 0;
}

int sum_positive_with_reduce(int *nums, int length) {
  UNUSED(nums);
  UNUSED(length);
  return 0;
}
