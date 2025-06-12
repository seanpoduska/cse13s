#include "final.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void should_be_exactly_equal(const char *message, int expected, int actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

ll_int *cons(int value, ll_int *node) {
  ll_int *out = calloc(1, sizeof(ll_int));
  out->val = value;
  out->next = node;

  return out;
}

int main(void) {
  ll_int *list = NULL;
  int lowest = 0;
  int nextlowest = 0;

  // make a list with some numbers in it.
  list = cons(10, list);
  list = cons(1, list);
  list = cons(15, list);
  list = cons(-15, list);

  find_two_lowest(list, &lowest, &nextlowest);
  should_be_exactly_equal("lowest should be -15", -15, lowest);
  should_be_exactly_equal("nextlowest should be 1", 1, nextlowest);

  return 0;
}
