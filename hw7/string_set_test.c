#include "string_list.h"
#include "string_set.h"

#include <stdbool.h>
#include <stdio.h>

void should_be_exactly_equal(const char *message, bool expected, bool actual) {
  printf("%s\n", message);
  printf("%s: wanted %d, got %d\n",
         (expected == actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {
  string_set *myset = make_empty_set();

  myset = add(myset, "hello");
  myset = add(myset, "avocado");
  should_be_exactly_equal("set has 'hello'", true, contains(myset, "hello"));
  should_be_exactly_equal("set has 'avocado'", true,
                          contains(myset, "avocado"));
  should_be_exactly_equal("set does not have 'dimetrodon'", false,
                          contains(myset, "dimetrodon"));

  myset = add(myset, "dimetrodon");
  should_be_exactly_equal("set should now have 'dimetrodon'", true,
                          contains(myset, "dimetrodon"));

  printf("should print 'hello', 'avocado' and 'dimetrodon' in some order\n");
  ll_string *entries = list_entries(myset);
  for (ll_string *here = entries; here; here = here->next) {
    printf("%s\n", here->value);
  }
  free_list(entries);
  free_set(myset);

  string_set *animals = make_empty_set();
  animals = add(animals, "kitty");
  animals = add(animals, "lizard");
  string_set *fluffy = make_empty_set();
  fluffy = add(fluffy, "cloud");
  fluffy = add(fluffy, "pillow");
  fluffy = add(fluffy, "kitty");

  string_set *animal_fluffy_intersection = set_intersection(animals, fluffy);
  entries = list_entries(animal_fluffy_intersection);
  printf("should print 'kitty'\n");
  for (ll_string *here = entries; here; here = here->next) {
    printf("%s\n", here->value);
  }
  free_set(animal_fluffy_intersection);
  free_list(entries);

  string_set *animal_fluffy_union = set_union(animals, fluffy);
  entries = list_entries(animal_fluffy_union);
  printf("should print 'kitty' 'lizard' 'cloud' 'pillow' in some order\n");
  for (ll_string *here = entries; here; here = here->next) {
    printf("%s\n", here->value);
  }
  free_set(animal_fluffy_union);
  free_set(animals);
  free_set(fluffy);
  free_list(entries);

  return 0;
}
