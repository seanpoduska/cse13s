#include "midterm.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void should_be_exactly_equal(const char *message, size_t expected,
                             size_t actual) {
  printf("%s\n", message);
  printf("%s: wanted %lu, got %lu\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

bool starts_with_capital(char *s) {
  if (s == NULL || strlen(s) < 1) {
    return false;
  }
  return (s[0] >= 'A' && s[0] <= 'Z');
}

int main(void) {
  // allocate space for some strings
  char **strings1 = calloc(4, sizeof(char *));
  strings1[0] = strdup("this string is all lowercase");
  strings1[1] = strdup("THIS STRING IS ALL UPPERCASE");
  strings1[2] = strdup("tHiS sTrInG AlTerNaTeS");
  strings1[3] = strdup("This String Is Title Case");

  should_be_exactly_equal(
      "two with a starting capital letter", 2,
      count_strings_with_property(starts_with_capital, strings1, 4));

  return 0;
}
