# homework 7: Hash tables, sets, I/O and strings

**Due date: Friday, 6 June 2025, 11:59pm**  (if you need longer it's ok)

# introduction

You know what used to work really well? [Search
engines](https://en.wikipedia.org/wiki/Search_engine). They seemed magical. The
idea that you could type a query into a search box and find documents, either in
some specific database, or on the [world wide
web](https://en.wikipedia.org/wiki/World_Wide_Web), that contained the search
terms that you had specified, was really exciting.

Let's build a tiny one!

# What are we searching for?

In this homework, we're working with a dataset called "[Twenty
Newsgroups](https://archive.ics.uci.edu/dataset/113/twenty+newsgroups)", which
contains about twenty thousand posts that were made on
[Usenet](https://en.wikipedia.org/wiki/Usenet) in 1993. This dataset was
collected by [Tom Mitchell](https://en.wikipedia.org/wiki/Tom_M._Mitchell) and
is fairly commonly used to teach text classification techniques in a machine
learning class.

The point here is, in a time before web forums, before Bluesky, before X The
Everything App, before Reddit, before Google+, people posted on Usenet to
discuss the topics they were passionate about -- Usenet forums were broadly used
to discuss a variety of topics (and occasionally to be rude on the Internet),
organized in a nice hierarchy so you had a sense about what each forum was
about. And we have a collection of a few thousand of these posts on a variety of
topics. We're going to finish building a search engine to find posts containing
specific terms.

## What the program does when it's finished

Once you're done, you'll have a working search engine that can look up documents
based on *queries*, which can contain one or more terms in them. There are two
kinds of queries, "or" and "and" queries.

An "or" query finds the posts in the database that contain *any* of the given
terms from the query -- the *set union* of the sets of documents that contain
each of those terms.

Conversely, an "and" query finds the posts in the database that contain *all* of
the given terms from the query -- the *set intersection* of the sets of
documents that contain each of those terms.

For example, if you were to do an *and* query for "baseball hockey", then this
would retrieve all of the posts in the database that contain the term "baseball"
*and also* the term "hockey". An *or* query would return many more documents --
every document that contains either of those terms (or both). Queries can
contain an arbitrary number of terms in them.

Once you have retrieved the documents, the program displays a list of their
subjet lines, and you may wish to read a particular post -- this can be done
with the "show" command, which will display the contents of a post based on its
number in the list of retrieved posts.

## What we know about each post

Our posts to the Usenet forums are contained in files, with one file per post --
so we have about twenty thousand files, organized into twenty directories.

Every post in the dataset has a variety of *headers* at the top of it. This
contains a lot of information about the post, which is independent of the
*content* in its body. Every line in the file before the first blank line is a
*header* line, and after the first blank line, we have the *content* of the
post.

The code to read a post's headers into a *metadata* structure is given to you.

The code to extract the *content* of a post is also given to you.

One thing to note about each message is that it is identified by a unique
`message_id`, and it may be *cross-posted*, which is to say that a message may
have been posted to several newsgroups simultaneously. As a result of this,
there are a nontrivial number of duplicate files in our dataset -- you don't
have to immediately deal with this (it is already handled in `main.c`), but just
know that some of the included files are duplicates of one another.

## Building our lookup tables

For this project, you will finish building the code for two different hash table
type datastructures.

One table, the *inverted index* in search engine terms, maps from every *term*
that is present in a post to a *set* of message IDs that contain that term. We
skip over terms that are in a set of "stop words", very commonly used function
words that are not considered to reflect the semantic content of the given
documents.

The other table maps from *message IDs* to a specific post metadata structure.

There are a few other things you'll need to finish implementing in order to make
everything work, which include the logic for "or" and "and" queries, a few
string utilities, and the logic for sets of strings.

## Queries

This search engine will offer two different querying modes, `AND` queries and
`OR` queries. In either case, the user can enter as many query terms as they
like.

If we are doing an `AND` query, then we will return and print only the documents
that contain *all* of the given search terms -- this is equivalent to taking the
*intersection* of the sets stored in the index.

If we are doing an `OR` query, then we will return and print the documents that
contain *any* of the given search terms -- this is equivalent to taking the
*union* of the sets stored in the index.

## Main interaction loop

On startup, the program loads the documents into memory and builds the
search index, as described above. Then we prompt the user for a command, and
continue until they either hit "ctrl+D" (sending the EOF signal) or type "quit".
The commands are as follows...

  * quit -- exit the program
  * help -- print a help message
  * `or <query>`  -- perform an "or" query with the specified terms
  * `and <query>` -- perform an "and" query with the specified terms
  * `show <resultnum>` -- if a previous query resulted in a list of posts, print
    out the (1-indexed) specified post

# Functions for you to finish

## string functions
These are in `index_lib.c`.

### `lowercase`
Change a string, *in place*, so that all of its characters are lowercase.

### `startswith`
Return `true` if the first string has the second string as a *prefix*, ie, if
the beginning of the first string is byte-for-byte equal to the second string.

## functions on sets of strings
These are in `string_set.c`. `string_set` is defined in terms of binary search
trees -- a string is either in the set, or it's not.

### `add`
Either returns the existing set (if the specified string is already in the set),
or expands the binary search tree to contain the new string.

### `contains`
Returns `true` if the specified string is in the set, otherwise `false`.

### `set_union`
Returns a *completely new* binary search tree that contains everything that is
in either of the specified sets. Allocates new nodes and new strings -- should
not contain any of the allocated memory from the component sets.

### `set_intersection`
Returns a *completely new* binary search tree that contains everything that is
in both of the specified sets (not just one set -- a string must occur in both
to be in the newly created set). Allocates new nodes and new strings -- should
not contain any of the allocated memory from the component sets.

### `free_set`
Free all of the memory associated with this string set -- all of the binary
search tree nodes as well as the associated strings.

### `list_entries`
Return a linked list (in any order) of all of the contents of this set.

## functions on the MetadataLookupTable
These are in the file `index_lib.c`.

### `store_metadata`

Add the specified `PostMetadata` structure into the MetadataLookupTable -- this
makes a complete copy of all of the fields, finds the appropriate place to store
it into the hash table, and puts it in there for later retrieval.

Does not need to deal with the question of whether that metadata has already
been stored in the table.

### `metadata_lookup`

Finds the specified `message_id` in the table, and if it is present, returns
the stored `PostMetadata` struct. Otherwise returns `NULL`. Does not make a copy
of the struct -- returns a pointer to the already allocated data structure.

### `free_metadata_lookup_table`
Frees all of the memory associated with the `MetadataLookupTable`.

## functions on the TermLookupTable
These are in the file `index_lib.c`.

### `add_message_id_to_term`
Add the specified message ID to the set of messages associated with the given
term. There may or may not be a `string_set` for the given term already in the
hash table -- if there is not one, create a new one. If a `string_set` exists,
add the `message_id` to that `string_set`.

### `term_lookup`
Returns the `string_set` for the specified term out of the hash table, if one
exists. If one does not exist, returns NULL. This function does not allocate a
new `string_set` -- it returns the already-allocated one stored in the hash
table.

### `free_term_lookup_table`
Frees all of the memory associated with the `MetadataLookupTable`.

### `union_lookup`
For the specified `ll_string` query, compute the union of all the messages
associated with each of the query terms in the given linked list. Computes a
completely new `string_set`, with fresh copies of all the included strings.

### `intersection_lookup`
For the specified `ll_string` query, compute the intersection of all the
messages associated with each of the query terms in the given linked list.
Computes a completely new `string_set`, with fresh copies of all the included
strings.

## Cleaning up our messes

For this homework, we are allocating various dynamic data structures (possibly
several of them), with `malloc` and `calloc`.

You need to make sure that we have a plan for `free`-ing all the memory we
allocate. Which parts of the code will allocate? How can you make sure every
allocated pointer gets `free`d?

In order to find out whether your code is cleaning up its messes, you should use
a tool called Valgrind.

If you have not yet installed Valgrind on your Linux system, you can install it
like so:
```
sudo apt install valgrind
```

You can run Valgrind to find out whether your program is leaking memory with the
following command:

```
valgrind --leak-check=full  ./searchengine
```

Valgrind will then tell you whether you are successfully cleaning up all of the
allocated memory, or whether your program has leaks.


## Grading rubric
  * 2 points for a DESIGN.md that reasonably discusses all of the problems
    you're going to have to face, and provides some prose descriptions of your
    plans, and/or some pseudocode. (Submit this by Wednesday in the separate
    Canvas assignment)
  * +1 point for each of the individual functions that you need to finish.

## deliverables

All of your deliverables for this homework should be checked in to a directory
called `hw7` in your CSE13s gitlab repository. Remember -- *add, commit, push*.

  * By **Thursday, 5 June 2025**, you should have written your `DESIGN.md`,
    containing your thoughts and plans and pseudocode for this assignment. You
    can change this after the fact, but get planning! This is a separate Canvas
    assignment.
  * All of your code!

## reading

You should read...
  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 6 (for some
    background on hash tables)
  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 7 (to
    understand the I/O happening here).
  * _The C Programming Language_ by Kernighan & Ritchie, Chapter 8 (more
    discussion of I/O, also an explanation of realloc).
