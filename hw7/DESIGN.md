# Homework 7: Design Document

	* author: Sean Poduska
	* date: June 4, 2025

# introduction
This assignment will work on creating a series of functions that help the user search for specific posts within our Usenet post database. 

# string functions
## lowercase
alters a specified string so all characters are lower case.
```
for each character in the string:
    if character is an uppercase letter:
        convert it to lowercase
```
## startswith
checks if a string has a matching start to a reference string.
```
for each character in prefix:
    if character does not match the corresponding character in main string:
        return false
return true
```

# functions on set of strings
## add
adds a string to a binary search tree. if already in the tree, return the existing set.
```
if set is NULL:
    create new set with this string
else if string already in set:
    return original set
else:
    insert string into correct location in binary search tree
return updated set

```
## contians
returns true if the specified string is in the specified set.
```
start at root of tree
while node is not NULL:
    if node’s string matches:
        return true
    else if string is less than node’s string:
        move left
    else:
        move right
return false

```
## set\_union
returns a new binary search tree that contains everything in either specified set.
```
create new empty set
for each string in first set:
    add to new set
for each string in second set:
    add to new set (duplicate check handled by add)
return new set

```
## set\_intersection
returns a new binary search tree that contians only the items in both specified sets.
```
create new empty set
for each string in first set:
    if string also in second set:
        add to new set
return new set

```
## free\_set
free all memory associated with a string set.
```
recursively:
    free left subtree
    free right subtree
    free string in node
    free node itself

```
## list\_entries
returns a linked list of all contents in a set.
```
initialize empty linked list
in-order traversal of BST:
    for each node:
        add node’s string to linked list
return linked list

```

# functions on the MetadataLookupTable
## store\_metadata
takes the metadata from a post and stores it in the MetadataLookupTable to be referenced later. 
```
allocate copy of PostMetadata
store all fields from given metadata
hash the message_id to get index
insert metadata into hash table at that index

```
## metadata\_lookup
fidns a specific message\_id from the table, if present, returns the stored PostMetadata struct pointer.
```
hash the message_id
go to corresponding hash bucket
search linked list for matching message_id
if found, return pointer to stored PostMetadata
else return NULL

```
## free\_metadata\_lookup\_table
frees all memory used by the Metadata lookup table.
```
for each bucket in table:
    for each item in linked list:
        free PostMetadata fields
        free metadata node
free hash table array

```

# functions on the TermLookupTable
## add\_message\_id\_to\_term
adds specified message\_id to the set of messages associated with the given term. if string set is not yet created, create one, if it already exists, add message\_id to that string set.
```
look up term in hash table
if not found:
    create new string_set
    add message_id to new set
    insert set into hash table under term
else:
    add message_id to existing set

```
## term\_lookup
returns the string set for a specified term out of the hash table. if string set doesn't exist, return NULL.
```
hash the term
look in corresponding bucket
if term found, return associated string_set
else return NULL

```
## free\_term\_lookup\_table
frees all memory used by MetadataLookupTable.
```
for each bucket:
    for each term:
        free string_set using free_set
        free term string and hash node
free hash table array

```
## union\_lookup
compute the union query of all specified messages, and returns a new string set with fresh copies of all included strings.
```
initialize result set to empty
for each query term in linked list:
    look up term in term lookup table
    if found:
        union result set with current term's set
return result set

```
## intersection\_lookup
	compute the intersection query of all specifed messages, and returns a new string set with fresh copies of all included strings.
```
initialize result set to NULL
for each query term in linked list:
    look up term in term lookup table
    if not found:
        return empty set (no doc contains all terms)
    else if result is NULL:
        set result to copy of current term’s set
    else:
        set result to intersection of result and current term’s set
return result set

```






