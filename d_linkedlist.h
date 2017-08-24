#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef D_LINKEDLIST_H_
#define D_LINKEDLIST_H_

// Alias for struct double_linked_list and enum boolean.
typedef struct double_linked_list dlinkedlist;
typedef enum boolean boolean;

// Generic structure for double_linked_list.
struct double_linked_list
{
	void *node_data;
	dlinkedlist *left_node_ptr;
	dlinkedlist *right_node_ptr;
};

// Create enum of boolean.
enum boolean
{
	false,	// false will be 0
	true
};

// List of function which can be use for the performing operations on the 
// double linked list.
boolean dAppendLeft(dlinkedlist**, void* const);
boolean dAppendRight(dlinkedlist**, void* coust);
void* dPopLeft(dlinkedlist**);
void* dPopRight(dlinkedlist**);
boolean dDelete(dlinkedlist**, const unsigned);
void dDeleteAll(dlinkedlist**);
void* dGetNodeData(dlinkedlist*, const unsigned);
void dDisplayAll(dlinkedlist*, void(*stringify_func)(void*));
int dFind(dlinkedlist*, void*, int(*compare_func)(void*, void*));
void dSort(dlinkedlist**, int(*compare_func)(void*, void*));
dlinkedlist* dReverse(dlinkedlist*);
dlinkedlist* dGetSubList(dlinkedlist*, unsigned, unsigned);
void dClone(dlinkedlist*, dlinkedlist**);

// Special functions which will used for allocation of heap memory, so that the
// at the time of exit all the allocated memory can be freed safly.
void* dMalloc(unsigned);
void dReleaseHeapMemories(void);

// Commonly used variables.
extern const unsigned DLINKEDLIST_SIZE;
extern dlinkedlist *d_heap_tracker___;

#endif // D_LINKEDLIST_H_