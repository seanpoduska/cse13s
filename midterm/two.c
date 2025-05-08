#include "midterm.h"

#include <stdio.h>

ll_float *delete_range(ll_float *list, float start, float end) {
	// delete ll_float head?
	ll_float *head = list;
	while (head != NULL && head->value >= start && head->value <= end) {
		ll_float *temp = head;
		head = head->next;
		free(temp);
	}

	// check for all other deletions
	ll_float *current = head;
	while (current != NULL && current->next != NULL) {
		if (current->next->value >= start && current->next->value <= end) {
			ll_float *temp = current->next;
			current->next = temp->next;
			free(temp);
		} else {
			current = current->next;
		}
	}
	
	return head;
}


