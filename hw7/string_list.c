#include "string_list.h"
#include <stdlib.h>
#include <string.h>

ll_string *cons(char *s, ll_string *list) {
  ll_string *out = calloc(1, sizeof(ll_string));
  out->next = list;
  out->value = strdup(s);

  return out;
}

ll_string *append(ll_string *list, char *s) {
  if (!list) {
    ll_string *out = calloc(1, sizeof(ll_string));
    out->next = list;
    out->value = strdup(s);
    return out;
  }
  list->next = append(list->next, s);
  return list;
}

ll_string *extend(ll_string *list, ll_string *addthese) {
  if (list) {
    list->next = extend(list->next, addthese);
    return list;
  } else if (addthese) {
    ll_string *out = calloc(1, sizeof(ll_string));
    out->value = strdup(addthese->value);
    out->next = extend(list, addthese->next);
    return out;
  } else {
    return NULL;
  }
}

ll_string *get_element(ll_string *list, size_t i) {
  if (!list || (i == 0)) {
    return list;
  } else {
    return get_element(list->next, i - 1);
  }
}

void free_list(ll_string *list) {
  if (!list) {
    return;
  }
  free_list(list->next);
  free(list->value);
  free(list);
}
