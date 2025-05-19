# Homework 6: Design Document

	* author: Sean Poduska
	* date: May 19, 2025

## introduction
This assignment will work on creating a solver for the wordle program we made in hw5.
The program could either be given the secret words for testing purposes, or exchange words to guess
with the user in order for them to successfully solve the puzzle, given past guesses and their
letter information.

## function 1: int score\_letter\(char letter, char \*\*vocabulary, size\_t num\_words)
Calculates how many words in the current vocabulary contain the given letter. Should ignore
eliminated words from this count.
Pseudocode:
```
int count = 0;
for (size_t i = 0; i < vocab_size; i++) {
	if (vocabulary[i] == NULL) continue;
	if (letter is found in vocabulary[i]) {
		count++;
	}
}
return count;
```

## function 2: int score\_word\(char \*word, int \*letter\_scores)
Calculates a score for a word based on how frequently its unique letters appear across the current vocab in order to pick guesses closer to the correct word.
Pseudocode:
```
bool seen[26] = {false};
int total = 0;
for each letter c in word {
    if (!seen[c - 'a']) {
        seen[c - 'a'] = true;
        total += score_letter(c, vocabulary, vocab_size);
    }
}
return total;
```

## function 3: char \*get\_guess\(char \*\*vocabulary, size\_t, num\_words)
Returns a guess word from the current vocabulary by choosing the word with the highest info gain
score. Best guess should look something like the pseudocode below
Pseudocode:
```
int max_score = -1;
char *best_word = NULL;
for (size_t i = 0; i < vocab_size; i++) {
	if (vocabulary[i] == NULL) {
		continue;
	}
	int score = score_word(vocabulary[i], vocabulary, vocab_size);
	if (score > max_score) {
		max_score = score;
		best_word = vocabulary[i];
	}
}
return best_word;
```

## function 4: size\_t filter\_vocabulary\_gray\(char letter, char \*\*vocabulary)
Removes words that contain the specified gray letter.
Pseudocode:
```
size_t count = 0;
for each word in vocabulary:
	if word is NULL: continue;
	if letter is in word:
		free word;
		set vocabulary[i] = NULL;
		count++;
return count;
```

## function 5: size\_t filter\_vocabulary\_yellow\(char letter, int position, char \*\*vocabulary, size\_t num\_words)
Removes words that do not contain a specified letter at a specified index.
Pseudocode:
```
size_t count = 0;
for (size_t i = 0; vocabulary[i] != NULL; i++) {
	if (letter is in vocabulary[i]) {
		free(vocabulary[i])size_t count = 0;
for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) continue;

    if (letter not in vocabulary[i] OR vocabulary[i][position] == letter) {
        free(vocabulary[i]);
        vocabulary[i] = NULL;
        count++;
    }
}
return count;
	}
}
```


## function 6: size\_t filter\_vocabulary\_green\(char letter, int position, char \*\*vocabulary, size\_t num\_words)
Removes any words that do not have a letter at a given position.
Pseudocode:
```
size_t count = 0;
for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) continue;

    if (vocabulary[i][position] != letter) {
        free(vocabulary[i]);
        vocabulary[i] = NULL;
        count++;
    }
}
return count;
```

## function 7: free\_vocabulary\(char \*\*vocabulary, size\_t num\_words)
Frees all non-null strings in vocabulary and then frees the array itself
Pseudocode:
```
for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] != NULL) {
        free(vocabulary[i]);
    }
}
free(vocabulary);
```

## test cases
```
Things to test in test cases:
score_letter correctness
score_word correctness
backing up vocabulary copies
filter_vocabulary_gray correctness
filter_vocabulary_yellow correctness
filter_vocabulary_green correctness
restoring vocabulary array after filtering
cleaning up test vocabulary (final deletion of vocabulary copies and edits)
```
