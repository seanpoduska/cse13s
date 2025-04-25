#include <stdio.h>

int multiply(unsigned int a, unsigned int b){
	unsigned int output = 0;
	for(unsigned int i = 0; i < b; i++){
		
		output += a;
	}

	return output;
}

int main(void) {
	printf("5 times 4 is: %d\n", multiply(5,4));
	return 0;
}


