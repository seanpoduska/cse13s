#include <stdio.h>
#include <stdbool.h>

int main(void){
	int num_lines = 0;
	int num_chars = 0;
	int num_a = 0;
	int num_e = 0;
	int num_i = 0;
	int num_o = 0;
	int num_u = 0;
	int num_other_chars = 0;

	while(true){
		int c = getchar();
		if (c == EOF){
			break;
		}
		// single quotes mean its one character
		if (c == '\n'){
			num_lines++;
		}
		if (c == 'a' || c == 'A'){
			num_a++;
		}
		else if (c == 'e' || c == 'E'){
			num_e++;
		}
		else if (c == 'i' || c == 'I'){
			num_i++;
		}
		else if (c == 'o' || c == 'O'){
			num_o++;
		}
		else if (c == 'u' || c == 'U'){
			num_u++;
		}
		num_chars += 1;
	}
	printf("a: %d, e:, %d, i: %d, o: %d, u: %d\n, 
			num_a, ");
	
}
