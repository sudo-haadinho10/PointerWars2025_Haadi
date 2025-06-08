#include "linked_list.h"

// Function pointers to (potentially) custom malloc() and
// free() functions.
//
static void * (*malloc_fptr)(size_t size) = NULL; //NULL initially points to nothing,holds no valid memory address
static void   (*free_fptr)(void* addr)    = NULL;

//Using the standard libc's malloc and free functions

struct linked_list * linked_list_create(void) {
	if(malloc_fptr==NULL){
		return NULL;
	}
	struct linked_list *l1=malloc_fptr(sizeof(struct linked_list));
	if(l1==NULL) {
		return NULL;
	}
	l1->head=NULL;
	return l1;
}

bool linked_list_delete(struct linked_list *ll) {
	if(ll==NULL) {
		return false;
	}
	struct node *curr=ll->head;
	struct node *temp;
	while(curr!=NULL) {
		temp=curr;
		curr=curr->next;
		free_fptr(temp);
	}
	ll->head=NULL;	
	return true;
}

size_t linked_list_size(struct linked_list *ll) {
	size_t size=0;
	if(ll==NULL) {
		return SIZE_MAX;
	}
	if(ll->head==NULL) {
		return 0;
	}
	struct node *curr=ll->head;
	while(curr!=NULL) {
		curr=curr->next;
		size+=1;
	}
	return size;
}

bool linked_list_insert_end(struct linked_list *ll,unsigned int data) {
	
	if(ll==NULL) {
		return false;
	}
	if(malloc_fptr==NULL){
                return NULL;
        }
	struct node *temp=malloc_fptr(sizeof(struct node));
	temp->data=data;
	temp->next=NULL;
	
	if(ll->head==NULL) {
		ll->head=temp;
		return true;
	}
	struct node *curr=ll->head;
	while(curr->next!=NULL) {
		curr=curr->next;
	}
	curr->next=temp;
	return true;
}

bool linked_list_insert_front(struct linked_list *ll,unsigned int data) {	
	if(ll==NULL) {
		return false;
	}
	if(malloc_fptr==NULL){
                return NULL;
        }
	struct node *temp = malloc_fptr(sizeof(struct node));
	temp->data=data;
	if(ll->head==NULL) {
		temp->next=NULL;
		ll->head=temp;
		return true;
	}
	temp->next=ll->head;
	ll->head=temp;
	return true;
}

bool linked_list_insert(struct linked_list *ll,	size_t index,unsigned int data) {
	if(ll==NULL) {
		return false;
	}
	if(ll->head==NULL && index>0) {
                return false;
        }

	if(index==0) {
		return linked_list_insert_front(ll,data);       
        }
	if(malloc_fptr==NULL){
                return NULL;
        }
	size_t tempindex=1;
	struct node *curr=ll->head;
	struct node *before;
	struct node *temp=malloc_fptr(sizeof(struct node));
	temp->data=data;
	temp->next=NULL;
	
	while(tempindex<index+1) {
		if(curr->next==NULL) {
			linked_list_insert_end(ll,data);
			return true;
		}
		before=curr;
		curr=curr->next;
		tempindex+=1;
	}
	before->next=temp;
	temp->next=curr;
	return true;
}

size_t linked_list_find(struct linked_list *ll,unsigned int data) {
	
	if(ll==NULL) {
		return SIZE_MAX;
	}
	if(ll->head==NULL) {
		return SIZE_MAX;
	}
	struct iterator *iter=linked_list_create_iterator(ll,0);
	while(iter->current_node!=NULL) {
		if(iter->data==data) {
			return iter->current_index;
		}
		linked_list_iterate(iter);
	}
	return SIZE_MAX;
}

bool linked_list_remove(struct linked_list *ll,size_t index) {
	
	if(ll==NULL) {
		return false;
	}
	if(ll->head==NULL) {
		return false;
	}
	if(malloc_fptr==NULL){
                return NULL;
        }
	struct node *curr=ll->head;	
	struct node *before=malloc_fptr(sizeof(struct node));
	
	 if(index==0 && curr->next==NULL) {
                free_fptr(curr);
                ll->head=NULL;
                return true;
        }
	if(index==0) {
		before=curr->next;
		free_fptr(curr);
		ll->head=before;
		return true;
	}
	
	while(index>0) {
		if(curr==NULL) {
			return false;
		}
		before=curr;
		curr=curr->next;
		index-=1;
	}
	before->next=curr->next;
	free_fptr(curr);
	return true;
}

struct iterator *linked_list_create_iterator(struct linked_list *ll,size_t index) {
	if(ll==NULL) {
		return NULL;
	}
		
	if(ll->head==NULL) {
		return NULL;
	}
	if(malloc_fptr==NULL){
                return NULL;
        }
	struct iterator *i1=malloc_fptr(sizeof(struct iterator));
	if(i1==NULL) {
		return NULL;
	}
	struct node *curr=ll->head;
	i1->ll=ll;
	i1->current_index=index;
	i1->data=curr->data;
	i1->current_node=ll->head;
	return i1;
 }
 

bool linked_list_delete_iterator(struct iterator *iter) {
	if(iter==NULL) {
		return false;
	}
	//free_fptr(iter->current_index);
	free_fptr(iter);
	return true;
}


bool linked_list_iterate(struct iterator * iter) {
	//iter->ll==NULL checked
	//
	if(iter==NULL) {
		return false;
	}
	if(iter->ll==NULL) {
		return false;
	}
	
	struct node *curr=iter->current_node;
	curr=curr->next;
	if(curr==NULL) {
		iter->current_node=NULL;
		return false;
	}
	iter->current_index+=1;
	iter->data=curr->data;
	iter->current_node=curr;
	return true;
}

bool linked_list_register_malloc(void *(*malloc)(size_t)) {
	if(malloc==NULL) {
		return false;
	}
	malloc_fptr=malloc;
	return true; //Success
}

bool linked_list_register_free(void (*free)(void*)){
	if(free==NULL) {
		return false;
	}
	free_fptr=free;
	return true;
}
