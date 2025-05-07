#include "midterm.h"

#include <stdio.h>
#include <stdlib.h>

void should_be_exactly_equal(const char *message, size_t expected,
                             size_t actual) {
  printf("%s\n", message);
  printf("%s: wanted %lu, got %lud\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {

  size_t *result = count_characters("elementary", "ey", 2);
  should_be_exactly_equal("3 'e's", 3, result[0]);
  should_be_exactly_equal("1 'y's", 1, result[1]);
  free(result);

  result = count_characters("this should work for long strings", "z", 1);
  should_be_exactly_equal("no z", 0, result[0]);
  free(result);

  return 0;
}
