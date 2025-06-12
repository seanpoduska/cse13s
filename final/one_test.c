#include "final.h"

#include <stdio.h>
#include <stdlib.h>

void should_be_exactly_equal(const char *message, size_t expected,
                             size_t actual) {
  printf("%s\n", message);
  printf("%s: wanted %lu, got %lu\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {

  // example from the README
  int **matrix1;
  matrix1 = calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    // now allocate each individual row, filled with 0 initially.
    matrix1[i] = calloc(3, sizeof(int));
  }
  matrix1[0][0] = 1;
  matrix1[1][0] = 2;
  matrix1[2][0] = 3;
  matrix1[3][0] = 4;
  matrix1[0][1] = 3;
  matrix1[1][1] = 4;
  matrix1[2][1] = 5;
  matrix1[3][1] = 6;
  matrix1[0][2] = 2;
  matrix1[1][2] = 2;
  matrix1[2][2] = 3;
  matrix1[3][2] = 5;

  should_be_exactly_equal("two strictly increasing colument", 2,
                          count_increasing_columns(matrix1, 4, 3));

  return 0;
}
