# Homework 2: Design Document

  * author: Sean Poduska
  * date: April 18 2025

## introduction

This homework assignment contains functions which perform a number of different calculations.
The main functions calculate collatz numbers in a sequence, as well as analyze the results in how many iterations it took to converge to zero. The calculator program is like a simple calculator which takes a file input and performs the operators given to it. This assignment might take a little bit more time than the last one, but it should still be simple enough.

## function 1: next\_collatz\_number\(int n)

Returns the integer value which is the next calculated collatz number \(halved if original number is even, tripled plus one if original number is odd.).

## function 2: count\_collatz\_steps\(int n)

Repeatedly calls next\_collatz\_number\(int n) until the returned number is 1 \(meaning it converged). Output of this function is the number of iterations of the collatz calculation in order to return a 1.

## function 3: maximum\(int \*nums, int len)

Returns the largest value in an array given the array location and its length.

## function 4: sum\_positive\(int \*nums, int len)

Returns the sum of all positive values found in an array given the array location and its length. Negative numbers will be skipped and will not be added to the sum.

## function 5: count\_negative\(int \*nums, int len)

Returns the quanity of negative elements found in an array given the array location and its length. Positive numbers will be skipped and will not be added to this count.

## the calculator program

Takes filename as argument, reads each line out of file into a string buffer \(done).
Line 1 has initial value for current running number, all numbers to be stored in type long.
Line 2 \(if found) arithmetic operator +,  -,  \*,  /.
Line 3 \(if found) Take current running number and operator and use to combine with number found on this line. Repeat last 2 lines for each line in file
Returns calculated computation, or "ERROR\n" if number is divided by 0.

