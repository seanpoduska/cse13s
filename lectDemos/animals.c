#include <stdio.h>
#include <stdlib.h>

typedef struct animal {
	char name[255];
	char species[255];
	int weight_kg;
	int num_legs;
	bool poisonous;
} Animal;

void print_animal(struct animal the_animal){
	printf("%s is a %s and they have %d legs and they are %s poisonous\n",
			the_animal.name, the_animal.species, the_animal.num_legs,
			the_animal.poisonous ? "very" : "not");
}

int main(void){
	Animal tom;	
	tom.num_legs = 4;
	tom.poisonous = false;
	strcpy(tom.name, "Tom The Giraffe", 255);
	strcpy(tom.species, "giraffe", 255);
	print_animal(tom);

	return 0;
}

