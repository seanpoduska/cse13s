/*
 * All of your code for hw3 goes in here. Your goal is to finish these
 * functions.
 */

#include "hw3.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool str_suffix(char *haystack, char *needle) {
	int len_haystack = strlen(haystack);
	int len_needle = strlen(needle);
	if (len_needle > len_haystack) {
		return false;
	}
	for (int i = 0; i < len_needle; i++) {
		if (haystack[len_haystack - len_needle + i] != needle[i]) {
			return false;
		}
	}
	return true;
}

char *str_repeat(char *s, int n) {
	int len_s = strlen(s);
	int total_length = len_s * n;
	char *out = malloc(sizeof(char) * (total_length + 1));
	if (out == NULL) {
		return NULL;
	}
	out[0] = '\0';
	for (int i = 0; i<n; i++) {
		strcat(out, s);
	}
	return out;
}

bool str_is_palindrome(char *s) {
	int left = 0;
	int right = strlen(s) - 1;
	while (left < right) {
		if (s[left] != s[right]) {
			return false;
		}
		left += 1;
		right -= 1;
	}
	return true;
}

float dot_product(float *vec_a, float *vec_b, int length) {
	float total = 0;
	for (int i = 0; i < length; i++) {
		total += (vec_a[i] * vec_b[i]);
	}
	return total;
}

int reduce(int *nums, int length, int (*f)(int, int), int initial) {
	int cumulative = initial;
	for (int i = 0; i < length; i++) {
		cumulative = f(cumulative, nums[i]);
	}
	return cumulative;
}

// These two functions will end up as a *single call to reduce*, but you'll have
// to write a new helper function for each of them. Those helper functions will
// be quite short though!

int max_f(int a, int b) {
	return (a > b) ? a : b;
	}

int maximum_with_reduce(int *nums, int length) {
	if (length == 0) {
		return 0;
	}
	return reduce(nums, length, max_f, nums[0]);
}

int add_pos(int cumulative, int next) {
	if (next > 0) {
		return cumulative + next;
	} else {
		return cumulative;
	}
}

int sum_positive_with_reduce(int *nums, int length) {
	return reduce(nums, length, add_pos, 0);
}
