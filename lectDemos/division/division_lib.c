#include <stdio.h>

#include "division_lib.h"

size_t division(size_t numerator, size_t denominator){
	size_t result = 0;
		
	while (numerator >= denominator){
		result += 1;
		numerator -= denominator;
	}
}
