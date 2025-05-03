# Homework 4: Design Document

  * author: Sean Poduska
  * date: May 2, 2025

## editor program
In this homework, I will build the very greatest text editing application that I have ever made for CSE 13s, in my whole life.

This text file editor program will be able to add, insert, delete, replace, duplicate text using functions which edit the file's linked list address. Several other functions of this assignemnt obtain the length of the specified linked list, as well as manipulate stacks that contain text and addresses in order to contain, copy, and manipulate text in the specified file. Overall, I think this assignment will be more challenging than the other previous assingments, but I dont think it would be too difficult, given what we have already covered on linked list manipulation and functions in the past.

## function 1: ll_text *append_text\(ll_text *list, char *text)
Takes a linked list and adds a new node to the end of the linked list, containing the new char to be added. Returns the new front of the linked list (shouldn't have changed).

## funciton 2: ll_text *insert_text\(ll_text *list, char *text, int position)
Adds a new node to a specified linked list in the specified position (position 0 will create a new head of the list, and increments by character after that.) Existing nodes will be pushed down 1 address in order to allocate for space. Returns linked list address front.

## function 3: ll_text *delete_text(ll_text *list, int position)
Takes in a linked list and deletes the node at the given position (position 0 being the start of the linked list). Nodes after given position are moved to fill empty node spot.

## function 4: ll_text *replace_text(ll_text *list, char *text, int position)
Takes in a linked list and the address of specified text, and replaces the contents of the list with the characters from the text address. Returns a pointer to the front of the text list.

## function 5: ll_text *duplicate_ll_text(ll_text *list)
Creates a copy of the text at the given text address including all text entries. Returns the address of the new list.

## function 6: int ll_text_length(ll_text *list)
Returns the length of the specified linked list. If empty, return 0 instead of NULL (Use iteration to count?).

## function 7: ll_text_stack *push_duplicate(ll_text_stack *stack)
Takes in a stack address and adds the entry to the front of the stack (Allocates new entry, makes that entry point at the existing one). Returns new stack address.

## function 8: ll_text_stack *push_empty(ll_text_stack *stack)
Takes in a stack address and creates a new empty stack a tthe top of the given stack. Contains no text. Return value is the top of the stack.

## function 9: ll_text_stack *pop_stack(ll_text_stack *stack)
Takes in a stack address and removes the top entry from the specified stack. Frees memory of popped entry. If removed last entry of a stack, return value is NULL stack address.
