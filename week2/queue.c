#include "queue.h"


void* (*malloc_fptr) (size_t size) =NULL;
void (*free_fptr)   (void *) =NULL;

bool queue_register_malloc(void * (*malloc)(size_t)) {
	if(malloc==NULL) {
		return false;
	}
	malloc_fptr=malloc;
	return true;
}

bool queue_register_free(void(*free)(void*)) {
	if(free==NULL) {
		return false;
	}
	free_fptr=free;
	return true;
}

// Creates a new queue.
// PRECONDITION: Register malloc() and free() functions via the
//               queue_register_malloc() and
//               queue_register_free() functions.
// Returns a new linked_list on success, NULL on failure.
//

struct queue *queue_create(void) {
	if(malloc_fptr==NULL) {
		return NULL;
	}
	struct queue *q = malloc_fptr(sizeof(struct queue));
	if(q==NULL) {
		return NULL;
	}
	//q->ll = malloc_fptr(sizeof(struct linked_list node));
	//if(q->ll==NULL) {
         //       return NULL;
        //}
	q->ll = linked_list_create();
	if(q->ll==NULL) {
		free(q);
		return NULL;
	}
	return q;
}

// Deletes a linked_list.
// \param queue : Pointer to queue to delete
// Returns TRUE on success, FALSE otherwise.
//

bool queue_delete(struct queue *queue) {
	if(free_fptr==NULL) {
		return false;
	}
	if(queue == NULL) {
		return false;
	}
	if(queue->ll==NULL) {
		free_fptr(queue);
		return false;
	}
	bool status = linked_list_delete(queue->ll);
	if(status==false) {
		return false;
	}
	free_fptr(queue);
	return true;
}

// Pushes an unsigned int onto the queue.
// \param queue : Pointer to queue.
// \param data  : Data to insert.
// Returns TRUE on success, FALSE otherwise.
// Queue follows FIFO
// enqueue at tail
//
bool queue_push(struct queue *queue,unsigned int data) {

	if(queue==NULL) {
		return false;
	}

	if(!linked_list_insert_end(queue->ll,data)) {
		return false;
	}
	//queue->head=queue->ll->head;
	//queue->tail=queue->ll->tail;
	//
	//printf("%d ",queue->ll->head->data);
	//printf("%lu ",queue->ll->size);
	return true;
}

// Pops an unsigned int from the queue, if one exists.
// \param queue       : Pointer to queue.
// \param popped_data : Pointer to popped data (provided by caller), if pop occurs.
// Returns TRUE on success, FALSE otherwise.
//

bool queue_pop(struct queue * queue, unsigned int * popped_data) {
	if(queue==NULL) {
		return false;
	}
	if(queue->ll == NULL) return false;
	
	if(queue_size(queue) == SIZE_MAX) {
		return false;
	}

	if(queue_size(queue) == 0) {
		return false;
	}

	//printf("size of queue\n%lu " ,queue_size(queue));

	//if(queue_size(queue)>=1) {
		//if(*popped_data == queue->ll->head->data) {
		//
	*popped_data=(queue->ll->head->data);
	if(!(linked_list_remove(queue->ll,0))) return false;
	return true;
	//	}
	//return false;
}

// Returns the size of the queue.
// \param queue : Pointer to queue.
// Returns size on success, SIZE_MAX otherwise.
//

size_t queue_size(struct queue *queue) {
	if(queue==NULL) {
		return SIZE_MAX;
	}
	return linked_list_size(queue->ll);
}

// Returns whether an entry exists to be popped.
// \param queue: Pointer to queue.
// Returns TRUE if an entry can be popped, FALSE otherwise.
//

bool queue_has_next(struct queue * queue) {
	if(queue==NULL) {
		return false;
	}
	if((queue_size(queue)==SIZE_MAX) || (queue->ll==NULL)){
		return false;
	}
	if(queue_size(queue)<=0) {
		return false;
	}
	if(queue_size(queue)>=1) {
		return true;
	}
	return false;
}

// Returns the value at the head of the queue, but does
// not pop it.
// \param queue       : Pointer to queue.
// \param popped_data : Pointer to popped data (provided by caller), if pop occurs.
// Returns TRUE on success, FALSE otherwise.
//
bool queue_next(struct queue * queue, unsigned int * popped_data) {
	if(queue==NULL) {
		return false;
	}
	if(queue->ll==NULL) {
		return false;
	}
	/*if(queue->ll->tail==NULL) {
		return false;
	}*/
	if(queue_size(queue)>=1) {
	//	if(queue->ll->tail->data==*popped_data) {
		*popped_data=queue->ll->head->data;
		return true;
	//}
		//return true;
	}
	return false;
}


