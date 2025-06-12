#include "final.h"

#include <stdio.h>
#include <string.h>

int is_removed(char c, char *toremove) {
  for (size_t i = 0; toremove[i] != '\0'; i++) {
    if (c == toremove[i]) {
      return 1;
    }
  }
  return 0;
}

char *remove_characters(char *text, char *toremove) {
  size_t len = strlen(text);
  char *result = malloc(len + 1);
  if (!result) {
    return NULL;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; i++) {
    if (!is_removed(text[i], toremove)) {
      result[j++] = text[i];
    }
  }
  result[j] = '\0'; // end string
  return result;
}
