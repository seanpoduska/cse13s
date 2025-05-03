# homework 4: stacks, linked lists, and some I/O

*Due date: Thursday, 8 May 2025, 11:59pm*

## introduction

The users have spoken loud and clear. vim is too hard to learn, VS Code has too
many options and is *the wrong color* by default, Emacs is bad for the tendons
in your hands, and Sublime Text costs $99 and the department won't let us
expense it.

The users need a new text editor, and we will provide.

In this homework, we will be building our own text editor, one that you could
actually use if you wanted to. Although honestly it would be pretty awkward.
*But you could!*

You're given the skeleton code for the implementation. All you have to do is
finish the specified functions, and you will have a working text editor!

Additionally, once your text editor is working correctly, if you want to make
further modifications to the interface or add more features, please do so! As
long as you don't change the specified library functions, make it amazing! Make
it your own. And tell us about what you did, if you want to share with the
class.

Like in previous homeworks, you will be given a header file and a Makefile,
neither of which you'll have to change, and a starter C source template, where
you will write your code. There are test cases for your code in
`editor_lib_test.c`. You will probably want to comment them out and focus on
making them work from the top to the bottom -- just run the tests for the
functions that you are ready to run.

As is the case for this class in general, you will need to write a `DESIGN.md`
file explaining your thought process for this homework, giving a little bit
of prose explaining what you're going to do. Seriously, give it some thought.
**This one is more involved than the previous homeworks**. It's getting real.

## getting started

In your gitlab repository, which you likely checked out into your home directory
on your Linux system, so it might be the directory `~/cse13s_sammytheslug` (if
you are Sammy The Slug), make a new directory called `hw4`.

```
$ cd ~/cse13s_sammytheslug
$ mkdir hw4
$ cd hw4
```

Then copy the following files into that directory, using `cp` (these are present
in the [cse-13s-resources-spring-2025
repository](https://git.ucsc.edu/cse-13s-spring-2025/cse-13s-resources-spring-2025), which
you should probably check out onto your computer):
  * `DESIGN.md` (design doc template)
  * `editor_lib.h` (you won't have to change this file)
  * `editor_lib.c` (this is where the majority of your work goes)
  * `editor.c` (you may wish to change this file)
  * `Makefile` (you won't have to change this file)
  * `editor_lib_test.c` (you *may* change this file -- it contains test cases
    for your code)

If you have already checked out the `cse-13s-resources-spring-2025` repository,
you can get the latest files in it by going into that directory and doing a `git
pull`.

## writing a design doc

Make a nice markdown file called `DESIGN.md` in your `hw4` directory, using the
given template if you like. In that file, ideally using some nice markdown
formatting (this is a good life skill), write a little bit about your plan for
for each of the functions in this homework. Check this in to your git repository
(and push!) by end-of-day on **Friday, 2 May 2025**.

Write at least one sentence -- probably a few -- about how you're going to
implement each of the nine functions. Give it some thought. Explain it to
yourself; explain it to your TA. Write down *what* you're going to do, *why*,
and *how*.

There is a separate assignment for this in Canvas, like in the previous
homeworks.

## how the editor works

### starting the editor

You can start the editor, once it's compiled, by typing:

```$ ./editor filename.txt```

This will open filename.txt if it already exists, or if it does not exist, you
will be able to save to that filename.

### available commands

See the `help` command in the editor -- it's in the `editor.c`!

### data structures
You'll be working with two kinds of data structures while implementing the text
editor.

At any given moment, the text in memory is represented by a linked list of lines
of text, which is the `ll_text` type in the code. If you have opened a new file,
then the linked list will be empty, or a `NULL` pointer!

Each entry in the linked list contains a field called `text`, which is just a
null-terminated string (and will typically not contain a newline, in memory),
and a field called `next`, which is a pointer to the next line if there is a
next line, or `NULL` if it's the final line.

The interesting feature of this editor, however, is its ability to *undo*. In
order to handle the undo operation, we have another data structure, the
`ll_text_stack`, which as you might imagine is a stack that contains `ll_text`s.

Every time we update the text, we push a new entry onto this stack and then do
our update on this new most recent stack entry. Take a look at how this works in
the main loop of `editor.c`.

Effectively, every time we do an editing operation, we create a new complete
state of the world. Then you can go back just by popping the stack -- this is
what the `undo` command does.

## the functions to write

Each of the functions have been *declared* in `editor_lib.h`, and their
initial *definitions* are in `editor_lib.c`. All you have to do is finish each
of these definitions. You can change all of the code that's in `editor_lib.c`,
but keep the function signatures and names the same.

For most of these functions, you could choose to write them iteratively, or
recursively. Some of them will make more sense in one style or the other. It's
up to you! Please write a few sentences about your plan for implementing each of
them in your design doc.

### `ll_text *append_text(ll_text *list, char *text)`

This function takes a linked list and adds a new node to the *end* of that list.
The new final node will contain a *copy* of the specified text. You'll have to
allocate the new linked list node and you'll probably want to use `strdup` to
copy the specified text.

The return value is the new front of the list -- usually this will be the same
as the current front of the list, but if `list` is `NULL`, you'll return the new
node that you just allocated.

### `ll_text *insert_text(ll_text *list, char *text, int position)`

This function takes a linked list and adds a new node to the list *in the
specified position*. If that position is, for example, 0, then the new head of
the list will be the new node that you allocate, but otherwise, you'll insert
your new node at the specified distance from the front. Like `append_text`,
you'll also want to copy the specified text so you have a fresh instance of the
text on the heap.

The return value is, again, the new front of the list.

It is guaranteed that there will be a sufficient number of nodes in the list --
this check happens in `editor.c`, go take a look! -- so you don't have to worry
about adding a node at position 3 for a list with only nodes in positions 0 and
1.

### `ll_text *delete_text(ll_text *list, int position)`

This function takes an `ll_text` linked list and deletes the node at the
specified position, keeping the rest of the list intact. If you've deleted from
the middle, then link the prior node to the deleted node's successor.

The return value is, again, the new front of the list (you might delete the 0th
entry, for example). If you've deleted the only node in the list, then the
return value will be `NULL`, an empty list.

### `ll_text *replace_text(ll_text *list, char *text, int position)`

This function goes to the node at the specified position, frees its text, and
then replaces that text with a copy of the given text. You'll again want to use
`strdup` to make a copy of that text so you have a fresh copy on the heap.

Returns a pointer to the front of the list. You are again guaranteed that
the specified position already exists in the list.

### `ll_text *duplicate_ll_text(ll_text *list)`

This function makes a *complete* copy of the specified `ll_text` linked list,
including its text entries. So you'll end up allocating as many `ll_text`
structs as were in the input list, and that same number of strings.

The output is the front of your *new* list.

### `int ll_text_length(ll_text *list)`

This function returns the length of the specified linked list. If it's `NULL`
(which will happen commonly), then the length is 0.

### `ll_text_stack *push_duplicate(ll_text_stack *stack)`

This function adds a new stack entry to the front of the specified stack (ie,
allocates a new stack entry and makes that stack entry point at the existing
one). The new stack entry will contain a complete copy of the `ll_text` linked
list that's at the top of the existing stack (think about what previous function
you might use to accomplish this).

You're guaranteed that the specified stack is not empty. The return value is the
new top of the stack.

### `ll_text_stack *push_empty(ll_text_stack *stack)`

This function creates a new *empty* stack entry at the top of the specified
stack. It's empty in the sense that its `ll_text` linked list contains no text.

The return value is the new top of the stack.

### `ll_text_stack *pop_stack(ll_text_stack *stack)`

This function removes the top entry in the specified stack. It also frees all
associated memory with that entry in the stack. This is central to our `undo`
functionality.

The return value is the new top of the stack, which might be NULL if you've
removed the only entry left.

If you take a look at `editor.c`, you can see that this is the central way that
we clean up memory in the editor. We just remove all the entries in the stack
and this frees all allocated memory.

## testing your code

You can build the tests for this code by running `make` and then the
`editor_lib_test` program, if everything built correctly.

```
$ make
$ ./editor_lib_test
```

If everything built and the test program prints out a bunch of SUCCESS messages,
then that is good evidence that your code is in good working order! You may wish
to think up some other test cases -- we'll be testing your code with similar but
distinct test cases during autograding.

You'll probably want to comment out most of the tests and gradually work
downward until they all pass. The tests will very likely crash until you have
the functions working; start roughly at the top.

## most importantly

If you write all the library functions correctly, *you will have a working text
editor* that you can use to edit text files! Give it a shot!

## checking for memory leaks 

In order to find out whether your code is cleaning up its messes, you should use
a tool called Valgrind.

You can install Valgrind on your Linux system like this:
```
sudo apt install valgrind
```

You can run Valgrind to find out whether your program is leaking memory with the
following commands:

```
valgrind --leak-check=full ./editor filename.txt

valgrind --leak-check=full ./editor_lib_test
```

Valgrind will then tell you whether you are successfully cleaning up all of the
allocated memory, or whether your program has leaks.

## show us what you've got: making the editor your own

If you find that you've built the whole editor and want to make it *awesome*,
please do make additional changes! You can add more functionality (searching?
lines longer than 1024 bytes? a more beautiful interface? syntax highlighting?),
you can change all the stuff in `editor.c` -- whatever you can dream up! Just
don't break the existing tests, and it will be great.

Please tell the instructor or your TA if you want to share what you've done, and
with your permission we'll share some of the most interesting editor extensions
with the class. We will post a form for you to tell us about your editor
extensions.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw4` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

The resources you need are available in this directory.

  * By **Friday, 2 May 2025**, you should have written your `DESIGN.md`,
    containing your thoughts and plans for this assignment, and
    submitted your DESIGN.md URL into the design doc assignment.
  * `editor_lib.c` -- your completed code goes here.
  * `editor_lib.h` -- you will not have to change the header file, but you
    should include it.
  * `editor_lib_test.c` -- the main function for exercising our code here. Feel
    free to write more test cases to make sure your program works on a variety
    of inputs!
  * `editor.c` -- the main function for running the editor!
  * Makefile -- make sure to turn this in too.

## grading rubric

You'll get one point each for correctly writing each function, and two points at
the grader's discretion for a reasonably coherent `DESIGN.md`, so up to 11
points total.

Bonus points and glory are available for making your editor extra cool!

## reading

You should read...

  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 5.
  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 6.
