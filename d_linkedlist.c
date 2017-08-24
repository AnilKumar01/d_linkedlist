#include "d_linkedlist.h"

///////////////////////////////////////////////////////////////////////////////
// Determine the size of linked list.
const unsigned DLINKEDLIST_SIZE = sizeof(dlinkedlist);

///////////////////////////////////////////////////////////////////////////////
// INSERTION OPERATIONS
// Implemenation of the dPushLeft funtion.
boolean dAppendLeft(dlinkedlist **ref_ptr, void* const node_data)
{
	// Allocate memory for the new node.
	dlinkedlist *new_node = (dlinkedlist*)malloc(DLINKEDLIST_SIZE);
	if(new_node == NULL)
		return false;
	
	new_node->left_node_ptr = NULL;
	new_node->right_node_ptr = NULL;
	new_node->node_data = node_data;

	// Attach the new node to the left of the ref_ptr of the linked list.
	if((*ref_ptr) == NULL)
		(*ref_ptr) = new_node;
	else
	{
		dlinkedlist *left_ptr = (*ref_ptr);
		while(left_ptr->left_node_ptr != NULL)
			left_ptr = left_ptr->left_node_ptr;

		left_ptr->left_node_ptr = new_node;
		new_node->right_node_ptr = left_ptr;
	}
	return true;
}

// Implementation of the dPushRight function.
boolean dAppendRight(dlinkedlist **ref_ptr, void* const node_data)
{
	dlinkedlist *new_node = (dlinkedlist*)malloc(DLINKEDLIST_SIZE);
	if(new_node == NULL)
		return false;

	new_node->left_node_ptr = NULL;
	new_node->right_node_ptr = NULL;
	new_node->node_data = node_data;

	// Attach the new node to the right of the ref_ptr of the linked list.
	if((*ref_ptr) == NULL)
		(*ref_ptr) = new_node;
	else
	{
		dlinkedlist *right_ptr = (*ref_ptr);
		while(right_ptr->right_node_ptr != NULL)
			right_ptr = right_ptr->right_node_ptr;

		right_ptr->right_node_ptr = new_node;
		new_node->left_node_ptr = right_ptr;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// DELETE OPERATIONS
// Implementation of pop left function.
void* dPopLeft(dlinkedlist **ref_ptr)
{
	if((*ref_ptr) != NULL)
	{
		while((*ref_ptr)->left_node_ptr != NULL)
			(*ref_ptr) = (*ref_ptr)->left_node_ptr;
		
		dlinkedlist *delete_node = (*ref_ptr);
		void *node_data = (*ref_ptr)->node_data;
		(*ref_ptr) = (*ref_ptr)->right_node_ptr;
		free(delete_node);

		return node_data;
	}
	
}

// Implementation of pop right function.
void* dPopRight(dlinkedlist **ref_ptr)
{
	if((*ref_ptr) != NULL)
	{
		while((*ref_ptr)->right_node_ptr)
			(*ref_ptr) = (*ref_ptr)->right_node_ptr;

		dlinkedlist * delete_node = (*ref_ptr);
		void *node_data = (*ref_ptr)->node_data;
		(*ref_ptr) = (*ref_ptr)->left_node_ptr;
		free(delete_node);

		return node_data;
	}	
}

// Implementation of boolean delete funtion.
boolean dDelete(dlinkedlist **ref_ptr, const unsigned node_index)
{
	unsigned index = 0;
	// Bring the ref_ptr to the left most node of the list.
	while((*ref_ptr)->left_node_ptr != NULL)
		(*ref_ptr) = (*ref_ptr)->left_node_ptr;
	
	dlinkedlist *delete_ptr = (*ref_ptr);

	if(node_index == index)
	{
		if( delete_ptr != NULL)
		{
			// Shift the ref_ptr to the 2nd left most node of the list.
			(*ref_ptr) = delete_ptr->right_node_ptr;
			// Set the left_node_ptr of the ref_ptr to the NULL.
			if((*ref_ptr) != NULL)
			{
				(*ref_ptr)->left_node_ptr = NULL;
			}

			// Set the right_node_ptr of the delete_ptr to NULL. i.e. detach
			// the node from the list.
			delete_ptr->right_node_ptr = NULL;
			// Free the memory allocated for the node_data and node.
			free(delete_ptr->node_data);
			free(delete_ptr);

			return true;
		}
	}
	else
	{
		index++;
		while(index < node_index)
		{
			if(delete_ptr->right_node_ptr == NULL)
				break;
			delete_ptr = delete_ptr->right_node_ptr;
			index++;
		}
		if(index == node_index && delete_ptr != NULL)
		{
			// Detach the node which has to delete.
			dlinkedlist *delete_node = (delete_ptr->right_node_ptr);
			delete_ptr -> right_node_ptr = (delete_ptr->right_node_ptr)->right_node_ptr;
			((delete_ptr->right_node_ptr)->right_node_ptr)->left_node_ptr = delete_ptr;

			// Free the memory used by the node_data in the delete_node.
			free(delete_node->node_data);
			// Free the delete node.
			free(delete_node);

			return true;
		}
	}
	return false;
}

// Implementation of dDeleteAll function.
void dDeleteAll(dlinkedlist **ref_ptr)
{
	// Bring the ref_ptr to the left most node of the list.
	while((*ref_ptr)->left_node_ptr != NULL)
		(*ref_ptr) = (*ref_ptr)->left_node_ptr;

	// Delete all node and its data.
	while((*ref_ptr) != NULL)
	{
		dlinkedlist *delete_node = (*ref_ptr);
		(*ref_ptr) = (*ref_ptr)->right_node_ptr;
		(*ref_ptr)->left_node_ptr = NULL;
		free(delete_node->node_data);
		free(delete_node);
	}
}

///////////////////////////////////////////////////////////////////////////////
// VIEW OPERATIONS
// Implementation of dGetNodeData function.
void* dGetNodeData(dlinkedlist *ref_ptr, const unsigned node_index)
{
	unsigned index = 0;
	// Bring the ref_ptr to the left most node of the list.
	while(ref_ptr->left_node_ptr != NULL)
		ref_ptr = ref_ptr->left_node_ptr;

	while(index <node_index)
	{
		if(ref_ptr->right_node_ptr == NULL)
			break;
		ref_ptr = ref_ptr->right_node_ptr;
		index++;
	}
	if(index == node_index && ref_ptr != NULL)
	{
		return ref_ptr->node_data;
	}
}

// Implementation of dDisplayAll function.
void dDisplayAll(dlinkedlist *ref_ptr, void(*stringify_func)(void*))
{
	// Bring the ref_ptr to the left most node of the list.
	while(ref_ptr->left_node_ptr != NULL)
		ref_ptr = ref_ptr->left_node_ptr;

	while(ref_ptr != NULL)
	{
		stringify_func(ref_ptr->right_node_ptr);
		ref_ptr = ref_ptr->right_node_ptr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// SEARCH OPERATIONS
// Implementation of dFind function.
int dFind(dlinkedlist *ref_ptr, void *key, int(*compare_func)(void*, void*))
{
	// Bring the ref_ptr to the left most node of the list.
	while(ref_ptr->left_node_ptr != NULL)
		ref_ptr = ref_ptr->left_node_ptr;

	int index = 0;
	while(ref_ptr != NULL)
	{
		if(compare_func(key, ref_ptr->node_data) == 0)
			return index;
		index++;
		ref_ptr = ref_ptr->right_node_ptr;
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// SORT OPERATIONS
// Implementation of dSort function.
void dSort(dlinkedlist **ref_ptr, int(*compare_func)(void*, void*))
{
	// Bring the ref_ptr to the left most node of the list.
	while((*ref_ptr)->left_node_ptr != NULL)
		(*ref_ptr) = (*ref_ptr)->left_node_ptr;

	dlinkedlist *itrate_ptr_0 = (*ref_ptr);
	while(itrate_ptr_0->right_node_ptr != NULL)
	{
		dlinkedlist *itrate_ptr_1 = itrate_ptr_0->right_node_ptr;
		while(itrate_ptr_1 != NULL)
		{
			if(compare_func(itrate_ptr_0->node_data, itrate_ptr_1->node_data) > 0)
			{
				void *tmp_node_data = itrate_ptr_0->node_data;
				itrate_ptr_0->node_data = itrate_ptr_1->node_data;
				itrate_ptr_1->node_data = tmp_node_data;
			}
			itrate_ptr_1 = itrate_ptr_1->right_node_ptr;
		}
		itrate_ptr_0 = itrate_ptr_0->right_node_ptr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// REVERSE AND COPY OPERATIONS
// Implemenation of dReverse function.
dlinkedlist* dReverse(dlinkedlist *ref_ptr)
{
	dlinkedlist *rev_list = NULL;
	// Bring the ref_ptr to the left most node of the list.
	while(ref_ptr->left_node_ptr != NULL)
		ref_ptr = ref_ptr->left_node_ptr;

	while(ref_ptr != NULL)
	{
		dAppendLeft(&rev_list, ref_ptr->node_data);
		ref_ptr = ref_ptr->right_node_ptr;
	}
	return rev_list;
}

// Implementation of dGetSubList function.
dlinkedlist* dGetSubList(dlinkedlist *ref_ptr, unsigned from_in, unsigned non)
{
	dlinkedlist *cpy_list = NULL;
	// Bring the ref_ptr to the left most node of the list.
	while(ref_ptr->left_node_ptr != NULL)
		ref_ptr = ref_ptr->left_node_ptr;

	unsigned index = 0;
	while(ref_ptr != NULL)
	{
		if(index++ >= from_in && non-- > 0)
		{
			dAppendRight(&cpy_list, ref_ptr->node_data);
		}
		ref_ptr = ref_ptr->left_node_ptr;
	}
	return cpy_list;
}

// Implementation of dClone function.
void dClone(dlinkedlist *from_ref_ptr, dlinkedlist **to_ref_ptr)
{
	// Bring the from_ref_ptr to the left most node of the list.
	while(from_ref_ptr->left_node_ptr != NULL)
		from_ref_ptr = from_ref_ptr->left_node_ptr;

	while(from_ref_ptr != NULL)
	{
		dAppendRight(&(*to_ref_ptr), from_ref_ptr->node_data);
		from_ref_ptr = from_ref_ptr->left_node_ptr;
	}
}

///////////////////////////////////////////////////////////////////////////////
// MEMORY MANAGEMENT OPERATIONS
// A garbage list which will keep track of all memory allocated through the
// sMalloc function.
dlinkedlist *d_heap_tracker___ = NULL;

// Implementation of memory allocation function.
void* dMalloc(unsigned nob)
{
	// Allocate memory for the request.
	void *heap_mem_ptr___ = malloc(nob);
	// Create new node for garbage list.
	dlinkedlist *new___ = (dlinkedlist*)malloc(DLINKEDLIST_SIZE);
	new___->node_data = heap_mem_ptr___;
	new___->left_node_ptr = NULL;
	new___->right_node_ptr = NULL;
	// Add the reference of the memory in the garbage list for tracking of 
	// all allocated memories.
	if(d_heap_tracker___ == NULL)
		d_heap_tracker___ = new___;
	else
	{
		new___->left_node_ptr = d_heap_tracker___;
		d_heap_tracker___->right_node_ptr = new___;
		d_heap_tracker___ = new___;
	}
	// Return the allocated memory reference.
	return heap_mem_ptr___;
}

// Implementation of release heap memory function.
void dReleaseHeapMemories(void)
{
	dDeleteAll(&d_heap_tracker___);
}