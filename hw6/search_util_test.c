// A nice place for you to mess with the functions, while you're developing.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "search_util.h"
int main(void) {
  char words[10][6] = {"stalk", "scrap", "shear", "batch", "motif",
                       "tense", "ultra", "vital", "ether", "nadir"};

  char **vocabulary = calloc(10, sizeof(char *));
  for (int i = 0; i < 10; i++) {
    vocabulary[i] = strdup(words[i]);
  }
  size_t num_words = 10;

  // --- score_word ---
  printf("\nTesting score_word...\n");
  int letter_scores[26];
  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }
  printf("score_word(\"stalk\") = %d\n", score_word("stalk", letter_scores));
  printf("score_word(\"eerie\") = %d (note: 'e' only counted once)\n", score_word("eerie", letter_scores));

  // --- score_letter ---
  printf("\nTesting score_letter...\n");
  printf("score_letter('x') = %d (expected 0)\n", score_letter('x', vocabulary, num_words));
  printf("score_letter('a') = %d (expected 5)\n", score_letter('a', vocabulary, num_words));

  // --- filter_vocabulary_green ---
  printf("\nTesting filter_vocabulary_green...\n");
  size_t green_filtered = filter_vocabulary_green('t', 2, vocabulary, num_words);
  printf("filter_vocabulary_green('t', 2) = %zu\n", green_filtered);

  // --- Reset vocabulary ---
  for (int i = 0; i < 10; i++) {
    free(vocabulary[i]);
    vocabulary[i] = strdup(words[i]);
  }

  // --- filter_vocabulary_yellow ---
  printf("\nTesting filter_vocabulary_yellow...\n");
  size_t yellow_filtered = filter_vocabulary_yellow('t', 0, vocabulary, num_words);
  printf("filter_vocabulary_yellow('t', 0) = %zu\n", yellow_filtered);

  // --- Reset vocabulary ---
  for (int i = 0; i < 10; i++) {
    free(vocabulary[i]);
    vocabulary[i] = strdup(words[i]);
  }

  // --- filter_vocabulary_gray ---
  printf("\nTesting filter_vocabulary_gray...\n");
  size_t gray_filtered = filter_vocabulary_gray('x', vocabulary, num_words);
  printf("filter_vocabulary_gray('x') = %zu (expected 0)\n", gray_filtered);
  gray_filtered = filter_vocabulary_gray('a', vocabulary, num_words);
  printf("filter_vocabulary_gray('a') = %zu (expected nonzero)\n", gray_filtered);

  // Clean up
  free_vocabulary(vocabulary, num_words);
  return 0;
}
