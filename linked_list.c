#include "linked_list.h"

// Function pointers to (potentially) custom malloc() and
// free() functions.
//
static void * (*malloc_fptr)(size_t size) = NULL; //NULL initially points to nothing,holds no valid memory address
static void   (*free_fptr)(void* addr)    = NULL;

//Using the standard libc's malloc and free functions


struct linked_list * linked_list_create(void){
	struct linked_list *l1=malloc_fptr(sizeof(struct linked_list));
	if(l1==NULL){
		return NULL;
	}
	l1->head=NULL;
	return l1;
}

bool linked_list_delete(struct linked_list *ll){
	if(ll==NULL){
		return false;
	}
	struct node *curr=ll->head;
	struct node *temp;
	while(curr!=NULL){
		temp=curr;
		curr=curr->next;
		free_fptr(temp);
	}
	ll->head=NULL;	
	return true;
}

bool linked_list_register_malloc(void *(*malloc)(size_t)){
	
	if(malloc==NULL){
		return 1;
	}

	malloc_fptr=malloc;
	return 0; //Success
}

bool linked_list_register_free(void (*free)(void*)){
	if(free==NULL){
		return 1;
	}
	free_fptr=free;
	return 0;
}
