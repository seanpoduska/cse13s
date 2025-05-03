# Homework 4: Design Document

  * author: Sean Poduska
  * date: May 2, 2025

## editor program

In this homework, I will build the very greatest text editing application that I
have ever made for CSE 13s, in my whole life.

This text file editor program will be able to 

## function 1: ll_text *append_text\(ll_text *list, char *text)
Takes a linked list and adds a new node to the end of the linked list, containing the new char to be added. Returns the new front of the linked list (shouldn't have changed).

## funciton 2: ll_text *insert_text\(ll_text *list, char *text, int position)
Adds a new node to a specified linked list in the specified position (position 0 will create a new head of the list, and increments by character after that.) Existing nodes will be pushed down 1 address in order to allocate for space. Returns linked list address front.

## function 3: ll_text *delete_text(ll_text *list, int position)


## function 4: ll_text *replace_text(ll_text *list, char *text, int position)

## function 5: ll_text *duplicate_ll_text(ll_text *list)

## function 6: int ll_text_length(ll_text *list)

## function 7: ll_text_stack *push_duplicate(ll_text_stack *stack)

## function 8: ll_text_stack *push_empty(ll_text_stack *stack)

## function 9: ll_text_stack *pop_stack(ll_text_stack *stack)

