#include "final.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void should_be_exactly_equal(const char *message, int expected, int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

void str_should_be_equal(const char *message, char *expected, char *actual) {
  printf("%s\n", message);
  printf("%s: wanted \"%s\", got \"%s\"\n",
         (!strcmp(expected, actual)) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {

  WordCountTable *table = build_word_count_table(10);
  increment_word_count("hello", table);
  increment_word_count("HELLO", table);
  increment_word_count("Hello", table);

  increment_word_count("different", table);

  int count = lookup_word_count("hellO", table);
  should_be_exactly_equal("should have hello 3 times", 3, count);

  return 0;
}
