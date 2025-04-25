# homework 3: strings, arrays and function pointers

*Due date: Tuesday, 29 April 2025, 11:59pm*

## introduction

In this homework, we will write some short functions that deal with strings,
arrays, and function pointers. We will introduce the ideas of `map` and `reduce`
in class (very shortly! on Wednesday!), and in this homework we'll be working
with `reduce`.

Like in previous homeworks, you will be given a header file and a Makefile,
neither of which you'll have to change, and a starter C source template, where
you will write your code. There are test cases for your code in `hw3_test.c`.
This homework contains more functions to write, but no standalone program. We'll
do more of those later!

As is the case for this class in general, you will need to write a `DESIGN.md`
file explaining your thought process for this homework and giving a prose
description of what you're doing, and that will be due on the Friday preceding
the main due date.

## getting started

In your gitlab repository, which you likely checked out into your home directory
on your Linux system, so it might be the directory `~/cse13s_sammytheslug` (if
you are Sammy The Slug), make a new directory called `hw3`.

```
$ cd ~/cse13s_sammytheslug
$ mkdir hw3
$ cd hw3
```

Then copy the following files into that directory, using `cp` (these are present
in the [cse-13s-resources-spring-2025
repository](https://git.ucsc.edu/cse-13s-spring-2025/cse-13s-resources-spring-2025/), which
you should probably check out onto your computer):
  * `hw3.h` (you won't have to change this file)
  * `Makefile` (you won't have to change this file)
  * `hw3_test.c` (you *may* change this file -- it contains test cases for your
    code)
  * `hw3.c` (this is where the majority of your work goes)
  * `DESIGN.md` (template design doc)

If you have already checked out the `cse-13s-resources-spring-2025` repository,
you can get the latest files in it by going into that directory and doing a `git
pull`.

```
$ cd ~/cse-13s-resources-spring-2025
$ git pull
```

## writing a design doc

Make a markdown file called `DESIGN.md` in your `hw3` directory. Write a
sentence or two about your plan for each of the seven functions in this
homework. Check this in to your git repository (and push!) by end-of-day on
**Friday, 25 April 2025**.

There is a separate assignment for this in Canvas, like in the previous
homeworks.

## the seven functions to write

Each of these functions have been *declared* in `hw3.h`, and their initial
*definitions* are in `hw3.c`. All you have to do is finish each of these
definitions. You can change all of the code that's in `hw3.c`, but keep the
function signatures and names the same. If you feel the need, you may include
more header files in `hw3.c`, but you probably won't have to.

### strings: is one string a suffix of the other?

Here you'll write `bool str_suffix(char *haystack, char *needle)`, which will
return `true` if the string `needle` is a suffix of the string `haystack`, ie,
that the haystack ends exactly with the needle.

For example, `"world"` is a suffix of `"hello world"`. But `"worlds"` is not a
suffix of `"hello world"`.

We guarantee that both of the parameters are valid null-terminated strings, but
they could be of any length -- for example, `needle` may be longer than
`haystack` (in which case it could not possibly be a suffix!), and either string
might be of length 0. The strings will not be NULL pointers.

What kind of an algorithm could you use to solve this? Will you do it
iteratively or recursively? You'll probably want to experiment with this on
paper or a whiteboard before starting to write the code. Write about your plan
in your design doc!

### strings: repeat a string *n* times

Here you'll write `char *str_repeat(char *s, int n)`, which will return a
*freshly allocated string* that consists of *n* repetitions of the input string
*s*.

For this function, you're going to need to allocate some memory and then return
a pointer to that memory. It is the caller's responsibility to free that memory,
not yours as the function implementer. See `hw3_test.c` for how a responsible
caller might free the memory.

If, for example, the user called `str_repeat("hello", 3)`, you would allocate
some space (how much? write about this in your design doc), and then write
`"hellohellohello"` into that space, and return that.

The parameter `n` is guaranteed to be 0 or greater. If it is 0, you should
return a freshly allocated empty string.

### strings: is this string a palindrome?

Here you'll write the function `bool string_is_palindrome(char *s)`, which will
return `true` if the given string is a
[palindrome](https://en.wikipedia.org/wiki/Palindrome), and `false` otherwise.
For the purposes of this problem, we want to ignore whitespace, punctuation,
numbers, and letter case. So as a simple example, the string `"bob"` is a
palindrome, but to get slightly fancier, so is `"Bob"`, or even `"Sit on a
potato pan, Otis"`.

This might seem tricky to write, but let me give you a hint -- one good strategy
out of many would be to allocate some scratch space to work with. It is your
responsibility to `free` any scratch space that you allocate before returning
from this function, and if you leak memory, this function will be considered
incorrect.

Checking for memory leaks with `valgrind` is described later in this document.

To answer the burning question you might have: a string with no ASCII letters in
it counts as a palindrome. So the empty string, or a string consisting only of
punctuation or whitespace or numbers, counts as a palindrome in a kind of
degenerate way. Technically correct -- the best kind of correct?

Feel free to look at [this nice Wikipedia
page](https://en.wikipedia.org/wiki/List_of_English_palindromic_phrases) for
more example palindromes to try, or suggest your own to the class!

### arrays: compute the dot product of two arrays

Here we'll consider two arrays of floats (which must be the same length), and
write `float dot_product(float *vec_a, float *vec_b, int length)` --
the [dot product](https://en.wikipedia.org/wiki/Dot_product) of two vectors.

The result of this function is the sum of all the pairwise products of the
corresponding elements of the two arrays.

### reduce

In class, we will talk about map and reduce, and we'll likely implement `map`.
And here in the homework, we're going to write `reduce`! Just because such a
notion is generally used in functional programming doesn't mean we can't build
it in C! (sometimes you had some formative programming experiences writing
[Scheme](https://en.wikipedia.org/wiki/Scheme_%28programming_language%29) and
[Common Lisp](https://en.wikipedia.org/wiki/Common_Lisp) and then you end up
teaching CS classes. These are relevant and used all the time in modern
programming, I promise.)

What does `reduce` do? It combines all of the elements in an array with a
specified function, cumulatively. It maintains a current cumulative value and
applies the function to the cumulative value and each element of the given
array in turn, in order to produce a new accumulator value. You might have
noticed that several functions from hw2 had a similar shape -- they had to look
at each element of a numerical array in turn and update a running value. Can we
abstract that behavior out somehow? We can! That's what `reduce` does.

Concretely, this is exactly analogous to
[`functools.reduce` in Python 3](https://docs.python.org/3/library/functools.html#functools.reduce).
And for your edification as a computer scientist, this is operation is often
called ["fold"](https://en.wikipedia.org/wiki/Fold_(higher-order_function)).

`reduce` will look like
`int reduce(int *nums, int len, int (*f)(int,int), int initial)`.

`initial` is the initial value of the cumulative value, and `f` is a pointer to
a function that takes two `int`s and returns an int -- the new value for the
cumulative function. When we're calling the function `f`, imagine that its first
parameter will be the current cumulative value, and the second parameter will be
the next item in the input array, and the function `f` will return the new value
for the cumulative value.

Why are we doing this? Well...

### finding the maximum element of an array with `reduce`

Having written `reduce`, you can now write `int maximum_with_reduce(int *nums,
int size)` -- this will do exactly the same thing as `maximum`, except that it
will consist entirely of a call to `reduce`.

You'll have to write a helper function here, one that takes two ints and returns
an int. What should it do? Write about this in your design doc!

Also, you will want to consider, what is a good initial cumulative value?  You
should take a look at `limits.h`, described in Section B.11 of Kernighan &
Ritchie.

### summing all of the positive elements of an array with `reduce`

Having written `reduce`, you can now write `int sum_positive_with_reduce(int
*nums, int size)` -- this will do exactly the same thing as `sum_positive`,
except that it will consist entirely of a call to `reduce` -- it can be written
in just one line!

You'll have to write a helper function here, one that takes two ints and returns
an int. What should it do?

## testing your code

You can build the tests for this code by running `make` and then the `hw3_test`
program, if everything built correctly.

```
$ make
$ ./hw3_test
```

If everything built and the test program prints out a bunch of SUCCESS messages,
then that is good evidence that your code is in good working order! You may wish
to think up some other test cases -- we'll be testing your code with similar but
distinct test cases during autograding.

## checking for memory leaks 

In order to find out whether your code is cleaning up its messes (especially in
`string_is_palindrome`), you should use a tool called Valgrind. *To be clear,
you probably won't need to free up memory in any other place.*

You can install Valgrind on your Linux system like this:
```
sudo apt install valgrind
```

You can run Valgrind to find out whether your program is leaking memory with the
following command:

```
valgrind --leak-check=full ./hw3_test
```

Valgrind will then tell you whether you are successfully cleaning up all of the
allocated memory, or whether your program has leaks.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw3` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

The resources you need are available in this directory.

  * By **Friday, 25 April 2025**, you should have written your `DESIGN.md`,
    containing your thoughts and plans for this assignment, and submitted your
    design doc URL into the design doc assignment.
  * `hw3.c` -- your completed code goes here.
  * `hw3.h` -- you will not have to change the header file, but you should
    include it.
  * `hw3_test.c` -- the main function for exercising our code here. Feel free to
    write more test cases to make sure your program works on a variety of
    inputs!
  * Makefile -- make sure to turn this in too.

## grading rubric

You'll get one point each for correctly writing each function, and two points at
the grader's discretion for a reasonably coherent `DESIGN.md`, so up to 9
points total.

## reading

You should read...

  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 5.
  * _The C Programming Language_ by Kernighan & Ritchie, Appendix B, section 11.
