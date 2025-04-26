# Homework 3: Design Document

  * author: Sean Poduska
  * date: April 25, 2025

## introduction

In this homework, I will work towards insights into my own feelings, introspect
about what makes me happy personally, and use these insights to improve my
appreciation and empathy for my fellow human beings. I may also write a few
functions in C.

This assignment focuses on creating functions which utilize arrays and sets of information in memory in order to perform calculations and work. A lot of these programs can scale up to use a lot of processing power if needing to work on large array inputs and strings.

## function 1: strings: is one a suffix of the other?
Will return true if the string needle is a suffix of the string haystack \(find if a string is a subset of another string). Still would run if needle string is longer than haystack string.

## function 2: strings: repeat a string n times
Returns a string that is n repetitions of input string s using allocated memory and pointers. \("Hello" would become "HelloHelloHello").

## function 3: strings: is this string a palindrome?
Returns true if the given string is a palindrome, and false otherwise. Should even work while ignoring whitespace, punctuation, numbers, and letter case. Useful to allocate space in order to work correctly and quickly.

## function 4: arrays: compute the dot product of two arrays
Returns the float result of the dot product between the two vecotrs \(given their pointers and integer length). \(Sum of all pairwise products of the corresponding elements of the two arrays.)

## function 5: reduce
Combines all of the elemetns in an array with a specified function, cumulatievly. Takes in an array, the first value being the current cumulative value, and does an operation on it with the second value in the array.

## function 6: finding maximum element of an array with reduce
Calls reduce in order to find the maximum element of an array. Will write a helper which takes in two integers and returns one \(array address, length, and answer).

## function 7: summing all of the positive elements of an array with reduce
Calls reduce in order to find the sum of all elements in an array. Should be formatted somewhat similar to the finding maximum element of an array funciton.
