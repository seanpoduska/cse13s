# homework 2: functions, arrays, and pointers

*Due date: Tuesday, 22 April 2025, 11:59pm*

## introduction

In this homework, we will write some short functions that deal with numbers and
arrays of numbers. We'll touch briefly on the relationship between pointers and
arrays, which we've been talking about recently in class.

Like in hw1, you will be given a header file and a Makefile, neither of which
you'll have to change, and a starter C source template, where you will write
your code. There are test cases for your code in `hw2_test.c`.

We will also write a tiny calculator program, which will read its input from a
file -- like in hw1, you may wish to copy these files into your hw2 directory
using the `cp` command. You are given skeleton code for doing this, but will
need to change the given code substantially according to the details in a
following section.

As is the case for this class in general, you will need to write a `DESIGN.md`
file explaining your thought process for this homework, writing a sentence or a
few sentences about each function (and the calculator program).
That will be due on the Friday preceding the main due date.

## getting started

In your gitlab repository, which you likely checked out into your home directory
on you Linux system, make a make a new directory called `hw2`. If you are Sammy
The Slug, it might be the directory `~/cse13s_sammytheslug`.

```
$ cd ~/cse_13s_sammytheslug
$ mkdir hw2
$ cd hw2
```

Then copy the following files into that directory, using `cp` (these are present
in the [cse-13s-resources-spring-2025
repository](https://git.ucsc.edu/ajrudnic/cse-13s-resources-spring-2025/), which
you should probably check out onto your computer):
  * `hw2.h` (you won't have to change this file)
  * `Makefile` (you won't have to change this file)
  * `hw2_test.c` (you *may* change this file -- it contains test cases for your
    code)
  * `hw2.c` (this is where the majority of your work goes)
  * `calculator.c` (you will write a program in here too)
  * `DESIGN.md` -- the beginning of the design document for hw2
  * Any test files that you want from the `hw2` directory -- take a look in
    there and see which ones you want! Use `ls` to look.

If you already have `cse-13s-resources-spring-2025` checked out onto your
computer, you can get the latest updates including all of these required files
by going into that directory and typing the command `git pull`.

## writing a design doc
Again for this homework, you've been given a template `DESIGN.md` to put in your
`hw2` directory. Write a sentence or two about your plan for each of the
functions in this homework, and also a few sentences about your plan for the
calculator.

Check this in to your git repository (and push!) by end-of-day on **Friday, 18
April 2025**. There is a separate assignment for this in Canvas, like in the
previous homework. Remember that for design docs, you'll submit the link to your
doc rather than a git hash.

## five functions to write

Each of these functions have been *declared* in `hw2.h`, and their initial
*definitions* are in `hw2.c`. All you have to do for these is finish each of
these definitions. You can change all of the code that's in `hw2.c`, but keep
the function signatures and names the same.

### computing the next Collatz number

The [Collatz conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture) is a
famous unproven conjecture in mathematics, which says that repeatedly applying a
simple function (which we'll specify shortly) to any positive number will
eventually converge on 1.

In this problem, we'll compute the *next* Collatz number for a given input
number. The formula is:

  * half the input number, if that number is even, *or*
  * (3 times the number) + 1, if that number is odd.

So in the function `int next_collatz_number(int n)`, just compute the next
number in the sequence and return it. For example, if `n` was 2, you should
return 1.

### counting Collatz steps to convergence

For this function, `int count_collatz_steps(int n)`, you'll repeatedly compute
the next Collatz number, until you reach a value of 1. This should return 0 if
the input is 1 -- it takes 0 steps for you to converge! And your output should
be 1 if the input is 2; one application of the above function gets you to a
value of 1, so it has converged after one step. And so on.

You could write this function either iteratively or recursively, and either
strategy will work fine! Which one will you pick? Write about it in your design
doc!

### finding the maximum element of an array

For this part of the homework, you will write a function
`int maximum(int *nums, int len)`, which takes an array of ints and its length,
and returns the maximum element of that array.

Make sure not to go past the end of the array! Remember that when we are passed
an array in C, we really just have the memory address of the first element, and
there is no particular way (inside the function) to know how much memory was
allocated for that array. *Question to ponder*: if you thought you
could use `sizeof` to get around this, what would happen?

You get our endless respect, but no extra credit, if you write a bit about why
you can't use `sizeof` to help you here in your design doc.

### summing all of the positive elements of an array

Here you will write a function `int sum_positive(int *nums, int len)`, which
again takes an array of ints and its length, and returns the sum of all of the
elements of that array *that are positive*.

Remember -- don't go past the end of the array.

### counting the negative numbers in an array

Finally, we will write `int count_negative(int *nums, int size)` -- this will
count up the number of negative elements in the given array. You might note that
the code for this function looks somewhat similar to the previous functions;
hold that intuition for a moment.

***Can you feel the spooky foreshadowing? ...***

## the calculator program

For this program, you are given `calculator.c` in the hw2 resources directory.

The calculator program will take a filename as an argument on the command line,
and read each line out of that file into a string buffer. This is already done
for you.

What you must then do is as follows:

  * The first line of the file contains a number (in base 10). This is your
    *initial value* for the current *running number*. Your running number should
    be stored in a variable of type `long`.
  * If there is a second line of the file, it is one of the arithmetic
    operators: `+ - * /`
  * There will always be an odd number of lines in the file, so if there was a
    second line there will be a third line, and that line will be another
    number. You must take your current *running number* and combine it with this
    newest number with the previous arithmetic operator. For every number you
    read in from the file, store it in a variable of type `long`.
  * If there are more lines of the file, then they are alternatingly operators
    and numbers.
  * You always update the current *running number* by combining it with the
    number that you just read from the file, using that specified arithmetic
    operator.

Your final output will then either be a single number with a single newline --
the answer, your completed computation -- or "ERROR" (with a newline) if you
ended up trying to divide by zero. You do not need to handle any other errors.

You might like to use the function `strtol` (see `man 3 strtol`) to convert
strings to longs. You might find some nice way to use function pointers here,
but that's just one design idea, and we haven't talked about those yet when this
homework released. You might also find nice ways to compare strings in
`<string.h>`.

You are given a few examples in the resources directory and should try them out.

Running the calculator program should look like this:

```
  $ ./calculator calc_example1_27.txt
```

And the output for running that should be exactly:

```
27
```

And then if you run:
```
  $ ./calculator calc_example2_error.txt
```

The output should be exactly:

```
ERROR
```

## testing your functions

You can build the tests for this code by running `make` and then the `hw2_test`
program, if everything built correctly.

```
$ make
$ ./hw2_test
```

If everything built and the test program prints out a bunch of SUCCESS messages,
then that is good evidence that your code is in good working order! You may wish
to think up some other test cases -- we'll be testing your code with similar but
distinct test cases during autograding.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw2` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

The resources you need are available in this directory.

  * By **Friday, 18 April 2025**, you should have written your `DESIGN.md`,
    containing your thoughts and plans for this assignment. If
    your initial plans did not work out (plans are worthless; planning is
    everything), you should update `DESIGN.md` for your final turnin.
  * `hw2.c` -- your completed code goes here.
  * `hw2.h` -- you will not have to change the header file, but you should
    include it.
  * `hw2_test.c` -- the main function for exercising our code here. Feel free to
    write more test cases to make sure your program works on a variety of
    inputs!
  * `calculator.c` -- your completed calculator program.
  * Makefile -- make sure to turn this in too. You should not change this.

## grading rubric

You'll get one point each for correctly writing each function, two points for
the working calculator, and two points the grader's discretion for a reasonably
coherent `DESIGN.md`, so up to 9 points. (2 in the first Canvas turnin, 7 in the
second one)

## reading

You should read...

  * _The C Programming Language_ by Kernighan & Ritchie, Chapters 3, 4 and 5.
  * _The C Programming Language_ by Kernighan & Ritchie, Appendix B, section 11.
