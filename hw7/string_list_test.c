#include "string_list.h"

#include <stdio.h>

int main(void) {

  ll_string *list1 = NULL;

  list1 = cons("everybody", list1);
  list1 = cons("afternoon", list1);
  list1 = cons("good", list1);

  ll_string *list2 = NULL;
  list2 = cons("searchtown", list2);
  list2 = cons("to", list2);
  list2 = cons("welcome", list2);

  list1 = extend(list1, list2);
  printf("about to print:\n");
  printf("good afternoon everybody welcome to searchtown \n");
  for (ll_string *here = list1; here; here = here->next) {
    printf("%s ", here->value);
  }
  printf("\n");

  free_list(list1);
  free_list(list2);

  return 0;
}
