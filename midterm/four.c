#include "midterm.h"

#include <stdio.h>

// PROBLEM 4
size_t *count_characters(char *s, char *count_these, size_t num_characters) {
	size_t *counts = calloc(num_characters, sizeof(size_t));
	
	for (char *p = s; *p != '\0'; p++) {
		for (size_t i = 0; i < num_characters; i++) {
			if (*p == count_these[i]) {
				counts[i]++;
				break; 
			}
		}
	}	
  return counts;
}
