#include "editor_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions about ll_text...
ll_text *append_text(ll_text *list, char *text) {
	// create new node
	ll_text *new_node = malloc(sizeof(ll_text));
	new_node -> text = strdup(text);
	new_node -> next = NULL;
	if (list == NULL) {
		return new_node;
	}
	ll_text *head_pointer = list;
	while (head_pointer -> next != NULL) {
		head_pointer = head_pointer -> next;
	}
	head_pointer -> next = new_node;
  return list;
}

void save_to_file(ll_text *list, const char *filename) {
  FILE *outfile = fopen(filename, "w");
	for (ll_text *here = list; here; here = here->next) {
    fprintf(outfile, "%s\n", here->text);
  }
	fclose(outfile);
}

int ll_text_length(ll_text *list) {
	int length = 0;
	while (list != NULL) {
		length++;
		list = list->next;
	}
  return length;
}

// insert a specific line: add to specific place in the linked list; this is the
// new entry at the specified line
ll_text *insert_text(ll_text *list, char *text, int position) {
	// create new node
	ll_text *new_node = malloc(sizeof(ll_text));
	if (new_node == NULL) {
		return list; // allocation failure
	}
	new_node -> text = strdup(text);
	new_node -> next = NULL;
	
	// if inserting at the head
	if (position == 0) {
		new_node->next = list;
		return new_node;
	}
	
	// find node before insert position
	ll_text *current = list;
	for (int i = 0; i < position - 1; i++) {
		current = current -> next;
	}
	
	//insert new node
	new_node -> next = current -> next;
	current -> next = new_node;
  return list;
}

// delete a specific line: delete the ith entry in the linked list and return
// the new front of the linked list.
ll_text *delete_text(ll_text *list, int position) {
	if (list == NULL) {
		return NULL;
	}
	
	// deleting head node
	if (position == 0) {
		ll_text *next = list -> next;
		free(list -> text);
		free(list);
		return next;
	}
	ll_text *prev = list;
	for (int i = 0; i < position - 1; i++) {
		if (prev -> next == NULL) {
			return list;
		}
		prev = prev -> next;
	}
	ll_text *to_delete = prev -> next;
	if (to_delete == NULL) {
		return list;
	}
	prev -> next = to_delete -> next;
	free(to_delete -> text);
	free(to_delete);
  return list;
}

// replace a line: go to the specific entry, free the text that's there, replace
// it with a copy of the specified text.
ll_text *replace_text(ll_text *list, char *text, int position) {
	if (list == NULL) {
		return NULL;
	}
	ll_text *current = list;
	
	// traverse to specified node
	for (int i = 0; i < position; i++) {
		current = current -> next;
	}
	
	// replace text
	free(current -> text);
	current -> text = strdup(text);
  return list;
}

// duplicate a list. Returns a copy of the list, including newly copied versions
// of all of the strings.
ll_text *duplicate_ll_text(ll_text *list) {
	if (list == NULL) {
		return NULL;
	}
	
	// create head of new list
	ll_text *new_head = malloc(sizeof(ll_text));
	new_head -> text = strdup(list -> text);
	new_head -> next = NULL;
	
	ll_text *current_old = list -> next;
	ll_text *current_new = new_head;
	
	// go through original list and copy nodes
	while (current_old != NULL) {
		ll_text *new_node = malloc(sizeof(ll_text));
		new_node -> text = strdup(current_old -> text);
		new_node -> next = NULL;
		
		current_new -> next = new_node;
		current_new = new_node;
		current_old = current_old->next;	
	}
  return new_head;
}

// functions about the state stack...
ll_text_stack *load_from_file(const char *filename) {
  ll_text *lines = NULL;
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  char buf[1024];
  FILE *infile = fopen(filename, "r");
  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    lines = append_text(lines, buf);
  }
  stack->lines = lines;
  fclose(infile);
  return stack;
}

ll_text_stack *new_stack_empty_text(void) {
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  stack->lines = NULL;
  return stack;
}

// Push a new state onto the stack that's an exact copy of the state currently
// at the top.
ll_text_stack *push_duplicate(ll_text_stack *stack) {
	// allocate new stack node
	ll_text_stack *new_top = malloc(sizeof(ll_text_stack));
	
	//duplicate list from top of stack
	new_top -> lines = duplicate_ll_text(stack -> lines);
	
	// link new node to original stack
	new_top -> next = stack;
  return new_top;
}

// Push a new entry onto the stack that has an empty ll_text at the top.
ll_text_stack *push_empty(ll_text_stack *stack) {
	// allocate new stack node
	ll_text_stack *new_top = malloc(sizeof(ll_text_stack));
	
	// set list pointer to NULL
	new_top -> lines = NULL;
	
	// link to original stack
	new_top -> next = stack;
  return new_top;
}

// undo, removing the most recent state
// this has to free all the memory associated with that state
ll_text_stack *pop_stack(ll_text_stack *stack) {
	if (stack == NULL) {
		return NULL;
	}
	
	// save next stack node before freeing
	ll_text_stack *next_stack = stack -> next;
	
	// free linked list inside stack entry
	ll_text *current = stack -> lines;
	while (current != NULL) {
		ll_text *next = current -> next;
		free(current -> text);
		free(current);
		current = next;
	}
	
	// free stack node itself
	free(stack);

	// return top of stack
  return next_stack;
}


// Find the first newline in the input and replace it with \0
void chomp(char *s) {
  for (int i = 0; s[i]; i++) {
    if (s[i] == '\n' || s[i] == '\r') {
      // Check for \r in case we're on Windows or a very old Mac??
      // Look, I won't stop you from doing CSE 13s on a Mac from 2001 or prior.
      s[i] = '\0';
      break;
    }
  }
}

