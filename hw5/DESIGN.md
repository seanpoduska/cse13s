# Homework 5: Design Document

  * author: Sean Poduska
  * date: May 12, 2025

## introduction

In this homework, I will implement a fun game to amuse and amaze my friends and
loved ones.



## wordle\_game.c: Main Function

This main function is the function which is run to start the program, and is the function that calls all other used functions. This function doesn't really need to be changed (unless for debugging and testing).

## wordle\_lib.c: score\_guess\(char *secret, char *guess, char *result)

Gives a score for the provided guess. If completely correct, returns True. If a letter is not used, return x in that spot. If a letter is in the wrong spot, return y in that spot. If a letter is correctly in place, return g in that spot.

## wordle\_lib.c: valid\_guess\(char *guess, char **vocabulary, size\_t num\_words)        

Checks if a given guess supplied by the user is valid, and returns a Boolean answer. Guess must contain only ASCII characters, be 5 characters long, and be found in the vocabulary dictionary in order to be valid.

## wordle\_lib.c: **load_vocabulary\(char *filename, size_t *num_words)

Returns an array of strings, where each string is a word from the provided file. num\_words is the provided file's word quantity. Allocating the correct amount of memory is necessary in order to operate cleanly. Freeing up memory is completed once the file is closed and the specified words are no longer needed.
