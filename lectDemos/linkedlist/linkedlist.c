#include <stdio.h>

typedef struct ll_int {
	int val;
	struct ll_int *next;
}	ll_int;

// add new item on front of ll
ll_int *cons(int val, ll_int *list) {
	// make new entry
	ll_int *new_front = calloc(1, sizeof(ll_int));
	new_front->val = val;

	new_front->next = list;
	
	// return that entry
	return new_front;
}

ll_int *add_to_back_iter(int val, ll_int *list) {
	ll_int *new_back = calloc(1, sizeof(ll_int));
	new_back->val = val;
	if (list == NULL) {
		return new_back;
	}
	ll_int *here = list;
	while (here->next) {
		here = here->next;
	} 
	here->next = new_back;
	return list;
}

void print_ll_int(ll_int *list) {
	printf("Heres a linked list:\n");
	for( ; list; list=list->next);
	while (list) {
		printf("list entry: %d\n", list->val)
	}
}

int main(void) {
	ll_int mylist = NULL;
	mylist = cons(10, mylist);
	return 0
}
