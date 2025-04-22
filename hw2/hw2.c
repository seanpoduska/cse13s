/*
 * All of your code for these five functions goes in here. These are for you to
 * finish. The code for the calculator is separate. Feel free to include more
 * headers or define helper functions if you want, but you can do this homework
 * without doing either.
 */

#include "hw2.h"

int next_collatz_number(int n) {
	if (n % 2 == 1) {
		return n * 3 + 1;
	} else {
		return n / 2;
	}
	return 0;
}

int count_collatz_steps(int n) {
	int count = 0;
	int num = n;
	while (num != 1) {
		count += 1;
		num = next_collatz_number(num);
	}
	return count;
}

int maximum(int *nums, int len) {
	int max = nums[0];
	for (int i = 1; i < len; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}
	return max;
}

int sum_positive(int *nums, int len) {
	int sum = 0;
	for (int i = 0; i < len; i++) {
		if (nums[i] > 0) {
			sum = sum + nums[i];
		}
	}
	return sum;
}

int count_negative(int *nums, int len) {	
	int count = 0;
	for (int i = 0; i < len; i++) {
		if (nums[i] < 0) {
			count += 1;
		}
	}
	return count;
}	
