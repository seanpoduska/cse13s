#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// let's just say there are 64 items in the world.
// can we get fancier later?

typedef unsigned long set;

set intersection(set a, set b) {
	return a & b;
}

set union(set a, set b) {
	return a | b;
}

void check_item(int item) {
	if (item < 0 || item > 63) {
		fprintf(stderr, "item must be in [0, 63]\n");
		assert(false);
	}	
}

// returns the set where we have turned on this position
set add(set a, int item) {
	if (item < 0 || item > 63) {
		fprintf("item must be in [0, 63]\n");
		assert(false);
	}
	// we have some pattern of bits
	// ensure that the thing in spot "item" is on
	return a | (1 << item);
}

bool contains(set a, int item) {
	check_item(item);

	return a & (1 << item);
}

void print_set(set theset) {
	printf("{ ");
	for (int i = 0; i < 64; i++) {
		if (contians(theset, i)) {
			printf("")
		}
	}
}

int main(void) {
	set myset = 0;
	set my_other_set = 0;

	myset = add(myset, 3);
	myset = add(myset, 5);
	myset = add(myset, 19);
	
	my_other_set = add(my_other_set, 19);

	printf("does myset contain 19? %d\n", contains(myset, 19));
	printf("does myset contain 20? %d\n", contians(myset, 20));

}
