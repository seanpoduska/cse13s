#include "final.h"

#include <stdio.h>

void find_two_lowest(ll_int *linkedlist, int *lowest, int *nextlowest) {
  // Your code here!
  if (!linkedlist || !linkedlist->next) return;

  int min1, min2;

  // init min1 and min2 first vals
  if (linkedlist->val < linkedlist->next->val) {
    min1 = linkedlist->val;
    min2 = linkedlist->next->val;
  } else {
    min1 = linkedlist->next->val;
    min2 = linkedlist->val;
  }

  ll_int *curr = linkedlist->next->next;
  while (curr) {
    if (curr->val < min1) {
      min2 = min1;
      min1 = curr->val;
    } else if (curr->val < min2) {
      min2 = curr->val;
    } else if (curr->val == min1) {
      min2 = min1;
    }
    curr = curr->next;
  }

  *lowest = min1;
  *nextlowest = min2;
  return;
}
