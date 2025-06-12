#include "final.h"
#include <stdio.h>

size_t count_increasing_columns(int **matrix, size_t rows, size_t cols) {
	size_t count = 0;
  for (size_t col = 0; col<cols; col++) {
    int increasing = 1;
    for (size_t row = 1; row < rows; row++) {
      if (matrix[row][col] <= matrix[row-1][col]) {
        increasing = 0;
        break;
      }
    }
    if (increasing) {
      count ++;
    }
  }
  return count;
}
