#include "final.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void should_be_exactly_equal(const char *message, char *expected,
                             char *actual) {
  printf("%s\n", message);
  printf("%s: wanted %s, got %s\n",
         !strcmp(expected, actual) ? "SUCCESS" : "FAILURE", expected, actual);
}

int main(void) {
  char *text = "Sphinx of black quartz, judge my vow";
  char *toremove = "aeiou";
  char *expected = "Sphnx f blck qrtz, jdg my vw";

  char *result = remove_characters(text, toremove);
  should_be_exactly_equal("should remove vowels not including y", expected,
                          result);

  return 0;
}
