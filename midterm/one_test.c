#include "midterm.h"

#include <stdio.h>
#include <stdlib.h>

void should_be_exactly_equal(const char *message, int expected,
                             int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

void should_be_positive(const char *message, int actual) {
  printf("%s\n", message);
  printf("%s: %d should be positive -- %s\n", message, actual,
         (actual > 0) ? "SUCCESS" : "FAILURE");
}

void should_be_negative(const char *message, int actual) {
  printf("%s\n", message);
  printf("%s: %d should be negative -- %s\n", message, actual,
         (actual < 0) ? "SUCCESS" : "FAILURE");
}

int main(void) {
  int increasing[] = {10, 20, 30, 9000};
  int decreasing[] = {0, -20, -30, -50};
  int neither[] = {0, -20, -30, -50, 9001};

  should_be_positive("increasing", array_sort_direction(increasing, 4));
  should_be_negative("decreasing", array_sort_direction(decreasing, 4));
  should_be_exactly_equal("neither increasing nor decreasing", 0, array_sort_direction(neither, 5));

  return 0;
}
