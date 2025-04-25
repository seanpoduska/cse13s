#include <stdbool.h>
#include <stdio.h>

int main(void) {
	int counts[26][26] = {{0}};
	char cur = '\0';
	char prev =  '\0';

	while (true){
	
		int c = getchar();
		if (c == EOF){
			break;
		}

		// if upper c, make lower
		if (c >= 'A' && c <= 'Z'){
			c = c - 'A' + 'a';
		}
		
		if (c >= 'a' && c <= 'z'){
			cur = c;
		}

		//if we have a previous letter, make a digraph
		if (prev ){
			counts[prev - 'a'][current - 'a'] += 1;
			printf("found digraph: %c%c\n", prev, cur);
		}

			
	}
	return 0;
}
