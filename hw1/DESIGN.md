# Homework 1: Design Document

  * author: Sean Poduska
  * date: April 9th, 2025

## introduction

In this homework, I will do the thing and solve important computer science
problems and probably win a
[Turing Award](https://en.wikipedia.org/wiki/Turing_Award) for doing so.

TODO(you):

In this assignment, I plan to create each of the following functions in methods described below. Each one seems reasonably straightforward and relatively easy to debug. This will be my first time \(outside of lecture) using Vim to create and run C programs, so I think finishing this assignment might take a little longer than expected, but it shouldn't be too hard after I learn a few more keyboard shortcuts.

## function 1: area\_of\_disk
Returns area of disk calculated from the equation A = Pi * r^2.
Inputs positive disk radius, and outputs area of disk in square units.
Uses M\_PI for pi from \<math.h>.

## function 2: area\_of\_ring
Returns area of ring calculated from subtracting area\_of\_disk\(inner\_ring) from area\_of\_disk\(outer\_ring).
Inputs positive outer and inner disk radii, and ouputs area of ring between disks. 
References area\_of\_disk\() function.

## function 3: bigger\_minus\_smaller
Returns absolute value of the difference of two given variables.
Inputs two separate variables, and outputs their positive difference.
Calculation with absolute value simplifies the program.

## function 4: value\_in\_range
Returns a boolean value whether or not the given value is within the provided range.
Inputs lower bound, a specific value, and an upper bound; Outputs either True of False.

## function 5: sum\_of\_greater\_squares
Returns the sum of the largest two values of the set of squares from given variables a, b, and c.
Inputs three separate variables, and outputs one value.
Square calculations will be first, then checking which squares are largest. Once those are found, their sum will be returned.

## the caat program
Returns string identical to input, but doubles each vowel in its place, including capitals.
Iterate through each character of string, using putchar\() to reprint it, but doubles printing of any character in set \{aeiouAEIOU}.

