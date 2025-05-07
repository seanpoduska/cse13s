#include "midterm.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool approximately_equal(double a, double b) {
  // difference is less than 0.001?
  return fabs(a - b) < 0.001;
}

void should_be_equal(const char *message, double expected, double actual) {
  printf("%s\n", message);
  printf("%s: wanted %f, got %f\n",
         approximately_equal(expected, actual) ? "SUCCESS" : "FAILURE",
         expected, actual);
}

// add a new float to the front of the list
ll_float *cons(float val, ll_float *list) {
  ll_float *new_front = calloc(1, sizeof(ll_float));
  new_front->value = val;
  new_front->next = list;
  return new_front;
}

int main(void) {

  ll_float *list = NULL;
  list = cons(50.0, list);
  list = cons(25.5, list);
  list = cons(10.0, list);
  list = cons(27.0, list);
  list = cons(9000.1, list);
  // list should now be 9000.1, 27.0, 10.0, 25.5, 50.0

  list = delete_range(list, 20.0, 29.9);

  should_be_equal("0th item", 9000.1, list->value);
  should_be_equal("1th item", 10.0, list->next->value);
  should_be_equal("2th item", 50.0, list->next->next->value);

  printf("also this should be a null pointer: %p\n",
         (void *)list->next->next->next);

  return 0;
}
