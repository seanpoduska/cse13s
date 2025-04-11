# homework 1: our first few functions in C

## Introduction
The aim of this assignment is to get you comfortable with writing functions in
C, and to help you understand how we can structure C programs across multiple
files. We'll talk about this in class, but this may be *your* first multi-file C
program, and it may be your first time using `make`.

This homework is due by *11:59pm on Tuesday, 15 April 2025*. The initial
version of the design doc is due by *11:59pm on Friday, 11 April 2025*, and
this is a separate assignment on Canvas.

## how this homework works

For this homework, you'll write five simple functions and complete the program
`caat`. The functions are declared for you already -- you just need to finish
their definitions.

You are given an initial version of `hw1.c`, in this repository, to start from.
You might notice that `hw1.c` does not include a `main` function! The `main`
here will be defined in another file, `hw1_test.c`. This helps us separate out
our code into a library of useful functions, and then the test code, which
exercises those functions.

This is a pattern that we want you to get comfortable with; we'll have library
functions in one C file and then the test code to exercise those library
functions in another C file. If we were building an application that *called*
those library functions, that would be still a third C file!

## getting started

In your gitlab repository, make a new directory called `hw1`. You likely checked
out your repository into your home directory on you Linux system, so it might be
the directory `~/cse13s_sammytheslug`. If you are Sammy The Slug, the process
will look like this:

```
$ cd ~/cse13s_sammytheslug
$ mkdir hw1
$ cd hw1
```

Then copy the following files into that directory, using `cp`:
  * `hw1.h` (you won't have to change this file)
  * `Makefile` (you won't have to change this file)
  * `hw1_test.c` (you *may* change this file, and it can be instructive to do
    just that -- it contains test cases for your code)
  * `hw1.c` (this is where the majority of your work goes)
  * `caat.c` -- our caat program
  * `DESIGN.md` -- the beginning of the design document for hw1

You might like to get these files from this very repository, which you can
clone if you navigate to
[its page on
gitlab](https://git.ucsc.edu/cse-13s-spring-2025/cse-13s-resources-spring-2025).

This process will look like:

```
$ cd ~
$ git clone git@git.ucsc.edu:cse-13s-spring-2025/cse-13s-resources-spring-2025.git
$ cd ~/cse13s_sammytheslug/hw1/
$ cp ~/cse-13s-resources-spring-2025/hw1/hw1.c .
```

Then repeat that last `cp` command, substituting each of the files you want
to copy. You can then use `ls` to make sure that you've copied all *six* files
that you need.

If you want to get fancy and save time, you can also use this command, which
will copy *all of the files* from the resources hw1 directory into your hw1
directory.

```
$ cd ~/cse13s_sammytheslug/hw1/
$ cp ~/cse-13s-resources-spring-2025/hw1/* .
```

## writing a design doc

You should now have an initial version of `DESIGN.md` in your `hw1` directory.
This is a text file that you should edit with your text editor! Work with the
existing formatting and extend it out to cover all the moving parts of this
homework. Also a short introduction.

This homework is relatively straightforward, but write a sentence or two about
your plan for each of the five functions in this homework, and a little bit
about how you think `caat.c` should work, in this file. Check this in to your
git repository (and push!) by end-of-day on **Friday, 11 April 2025**. For
design docs, instead of the commit ID, copy the link to your design doc into the
text box.

### a note about markdown

[Markdown](https://en.wikipedia.org/wiki/Markdown) is a simple markup language
for formatting documents with a lightweight syntax -- it's meant to be editable
with a simple text editor, perhaps the same one you use for writing code, and is
less work than writing HTML by hand, and also less work than making a PDF
document with [LaTeX](https://en.wikipedia.org/wiki/LaTeX). It's supported on a
variety of platforms; it's really very popular. Notably for software developers,
it's commonly used on GitLab and GitHub, and it's a popular choice for
formatting blog posts. This very README (like most READMEs, on software projects
hosted on GitHub and GitLab) is a markdown document!

So please do learn some Markdown formatting, and get proficient at it!

Make a separate section for each of the six things you're building in this
homework (section headers start with `#` or `##`, depending on how big you want
the font) -- you're writing five small functions and the `caat` program.

The URL for your design doc will look something like:

```
https://git.ucsc.edu/cse-13s-spring-2025/cse13s_sammytheslug/-/blob/main/hw1/DESIGN.md
```

... so please paste that (but your actual URL) into the text box on Canvas.
*Double check that your link works and that your document looks good* by
visiting that URL in your web browser and taking a look at it! A nice document
goes a long way!

Have some professional pride here -- you're becoming a software developer, and
if you're any kind of good engineer, you're going to write quite a lot of prose.
Maybe more prose than code even.

## five functions to write

Each of these functions have been *declared* in `hw1.h`, and their initial
*definitions* are in `hw1.c`. All you have to do is finish each of these
definitions. You can change all of the code that's in `hw1.c`, but keep the
function signatures and names the same.

### `area_of_disk`

This function takes the radius of a disk, and returns its area, using the
familiar *A = Pi * r<sup>2</sup>* formula for the area of a circle. You'll be
given a positive radius here. Note that you can get a good value for Pi with the
constant `M_PI`, which is defined in `<math.h>`.

### `area_of_ring`

This function, given the outer radius of a disk, and the inner radius of *the
hole in the disk* (picture a compact disc -- remember physical media?), returns
the area of that disk.

### `bigger_minus_smaller`

This function figures out which of the two given numbers is greater, and then
returns the greater number minus the lesser number.

### `value_in_range`

This function, given three numbers (a lower bound, a specific value, and an
upper bound), returns `true` if the value is in the range *[lower, upper]*,
(inclusive) and false otherwise. Any or all of the parameters might be negative,
but the upper bound is guaranteed to be greater than the lower bound.

### `sum_of_greater_squares`

This function, given three numbers `a`, `b`, and `c`, returns the sum of the
two greatest squares, out of *a<sup>2</sup>*, *b<sup>2</sup>*, and
*c<sup>2</sup>*. Note that any of these numbers might be negative (or zero), and
the square of a large negative number is positive.

## testing your code

You can build the tests for this code by running `make` and then the `hw1_test`
program, if everything built correctly.

```
$ make
$ ./hw1_test
```

If everything built and the test program prints out a bunch of SUCCESS messages,
then that is good evidence that your code is in good working order! You may wish
to think up some other test cases -- we'll be testing your code with similar but
distinct test cases during autograding.

## the `caat` program

For your next task, finish the program `caat.c`. This program will take in each
character from `stdin`, one at a time, using `getchar()` and output every
character to `stdout` using `putchar()`. WITH ONE EXCEPTION. For any English
vowel, any one of the characters `aeiouAEIOU`, output that character *twice*. Do
not produce any other output. (it will upset the autograder script)

And then make sure to stop as soon as you find an `EOF` character! That's the
end of the input.

If your program has been implemented correctly, you should be able to run the
following command:

```
cat input_text.txt | ./caat
```

... and the output will look *exactly* like the following:

```
Scootoophaaeeuus blaackwaallii, aalsoo knoown aas thee moouusee spiideer, iis aa speeciiees oof spiideer beeloongiing too thee faamiily Gnaaphoosiidaaee.

Thiis speeciiees iis wiideespreeaad iin Briitaaiin aand noortheern EEuuroopee. Theey aaree coommoonly foouund iin Briitaaiin aaroouund aand iinsiidee hoouusees, uusuuaally iin thee AAuutuumn, aand aalsoo uundeer baark aand iin hoolees iin waalls iin waarmeer paarts oof EEuuroopee. IIt huunts nooctuurnaally.
```

`input.txt` comes from the Wikipedia page on the spider [Scotophaeus
blackwalli](https://en.wikipedia.org/wiki/Scotophaeus_blackwalli).

We did some examples in class dealing with `getchar()`, which you might find
helpful, and [those are
here](https://git.ucsc.edu/cse-13s-spring-2025/demos-spring-2025/-/tree/main/count_characters).

## a note about formatting

Like we talked about in class, C as a language does not care how, or in fact
whether, you indent your code. But if you'd like to keep your code neat and
tidy, you may wish to run the standard clang formatter, `clang-format`, on your
code before turning it in. Or just whenever you feel like it! To do this, you
can just run:

```
  $ make format
```

... which will call the formatter on your code for you.

If you do not have clang-format installed yet, you may need to install it with:

```
  $ sudo apt install clang-format
```

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw1` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

  * `DESIGN.md` -- due on the Friday.
  * `hw1.c`
  * `caat.c`
  * `hw1_test.c` (you can add or change the test cases if you like)
  * `hw1.h` (should be unchanged from the initial version)
  * `Makefile` (should be unchanged from the initial version)

Then, crucially, upload your commit ID to Canvas!

You can find the most recent commit ID by using `git log` or searching for it
through the GitLab web interface. Your assignment is turned in only after you
have pushed and submitted the commit ID you want graded on, Canvas. Don't
forget!

*Note in general* -- you want to put a git commit ID into the box on Canvas that
is *your last git commit ID* for the work you've done on a homework. Don't put
more than one! Don't put an earlier git commit ID! Either of these things will
break autograding, and then you won't get credit for your work.

## grading rubric

You'll get one point each for correctly writing each function, one point for
`caat.c`, and two points at the grader's discretion for a reasonably coherent
`DESIGN.md`, so up to 8 points.

## reading

You should read...

  * *The C Programming Language* by Kernighan & Ritchie. Chapter 1.
  * *The C Programming Language* by Kernighan & Ritchie. Chapter 2.
  * https://about.gitlab.com/blog/2018/08/17/gitlab-markdown-tutorial/
