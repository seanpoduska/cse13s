#include "midterm.h"

int array_sort_direction(int *arr, size_t len) {
	if (len < 2) {
		return 0;
	}
	
	int increasing = 1;
	int decreasing = 1;
	
	for (size_t i = 1; i < len; i++) {
		if (arr[i] <= arr[i - 1]) {
			increasing = 0;
		}
		if (arr[i] >= arr[i - 1]) {
			decreasing = 0;
		}
	}
	
	if (increasing) {
		return 1;
	} else if (decreasing) {
		return -1;
	} else {
		return 0;
	}
}


