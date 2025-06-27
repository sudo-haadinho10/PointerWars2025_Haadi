#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>

#include "linked_list.h"

//Definition of the queue
//
struct queue {
	struct linked_list *ll;
	//struct node *head;
	//struct node *tail;
};

// Creates a new queue.
// PRECONDITION: Register malloc() and free() functions via the
//               queue_register_malloc() and
//               queue_register_free() functions.
// Returns a new linked_list on success, NULL on failure.
//
struct queue *queue_create(void);

// Deletes a linked_list.
// \param queue : Pointer to queue to delete
// Returns TRUE on success, FALSE otherwise.
//
bool queue_delete(struct queue * queue);

// Pushes an unsigned int onto the queue.
// \param queue : Pointer to queue.
// \param data  : Data to insert.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_push(struct queue * queue, unsigned int data);

// Pops an unsigned int from the queue, if one exists.
// \param queue       : Pointer to queue.
// \param popped_data : Pointer to popped data (provided by caller), if pop occurs.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_pop(struct queue * queue, unsigned int * popped_data);

// Returns the size of the queue.
// \param queue : Pointer to queue.
// Returns size on success, SIZE_MAX otherwise.
//
size_t queue_size(struct queue * queue);

// Returns whether an entry exists to be popped.
// \param queue: Pointer to queue.
// Returns TRUE if an entry can be popped, FALSE otherwise.
//
bool queue_has_next(struct queue * queue);

// Returns the value at the head of the queue, but does
// not pop it.
// \param queue       : Pointer to queue.
// \param popped_data : Pointer to popped data (provided by caller), if pop occurs.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_next(struct queue * queue, unsigned int * popped_data);

// Registers malloc() function.
// \param malloc : Function pointer to malloc()-like function.
// POSTCONDITION: Initializes malloc() function pointer in linked_list.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_register_malloc(void * (*malloc)(size_t));

// Registers free() function.
// \param free : Function pointer to free()-like function.
// POSTCONDITION: Initializes free() functional pointer in linked_list.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_register_free(void (*free)(void*));

#endif
