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

struct queue *queue_create(void);

bool queue_delete(struct queue * queue);

bool queue_push(struct queue * queue, unsigned int data);

bool queue_pop(struct queue * queue, unsigned int * popped_data);

size_t queue_size(struct queue * queue);

bool queue_has_next(struct queue * queue);

bool queue_next(struct queue * queue, unsigned int * popped_data);

bool queue_register_malloc(void * (*malloc)(size_t));

bool queue_register_free(void (*free)(void*));

#endif
