#include "linked_list.h"

// Function pointers to (potentially) custom malloc() and
// free() functions.
//
static void * (*malloc_fptr)(size_t size) = NULL; //NULL initially points to nothing,holds no valid memory address
static void   (*free_fptr)(void* addr)    = NULL;

//Using the standard libc's malloc and free functions

// Creates a new linked_list.
// PRECONDITION: Register malloc() and free() functions via the
//               linked_list_register_malloc() and 
//               linked_list_register_free() functions.
// POSTCONDITION: An empty linked_list has its head point to NULL.
// Returns a new linked_list on success, NULL on failure.
//

struct linked_list * linked_list_create(void) {
	if(malloc_fptr==NULL){
		return NULL;
	}
	struct linked_list *l1=malloc_fptr(sizeof(struct linked_list));
	if(l1==NULL) {
		return NULL;
	}
	l1->head=NULL;
	l1->size=0;
	return l1;
}

// Deletes a linked_list.
// \param ll : Pointer to linked_list to delete
// POSTCONDITION : An empty linked_list has its head point to NULL.
// Returns TRUE on success, FALSE otherwise.
//

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
		ll->size-=1;
	}
	ll->head=NULL; 
	free_fptr(ll);	
	return true;
}

/*size_t linked_list_size(struct linked_list *ll) {
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
}*/

// Returns the size of a linked_list.
// \param ll : Pointer to linked_list.
// Returns size on success, SIZE_MAX on failure.
//

size_t linked_list_size(struct linked_list *ll) {
	if(ll==NULL){
		return SIZE_MAX;
	}
	return ll->size;

}

// Inserts an element at the end of the linked_list.
// \param ll   : Pointer to linked_list.
// \param data : Data to insert.
// Returns TRUE on success, FALSE otherwise.
//

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
	
	//Case 1: Empty linked_list
	//
	if(ll->head==NULL) {
		ll->head=temp;
		ll->size+=1;
		return true;
	}
	struct node *curr=ll->head;

	//Case 2 Non Empty Linked Lists
	//
	while(curr->next!=NULL) { 
		curr=curr->next;
	}
	curr->next=temp;
	ll->size+=1;
	return true;
}

// Inserts an element at the front of the linked_list.
// \param ll   : Pointer to linked_list.
// \param data : Data to insert.
// Returns TRUE on success, FALSE otherwise.
//

bool linked_list_insert_front(struct linked_list *ll,unsigned int data) {	
	if(ll==NULL) {
		return false;
	}
	if(malloc_fptr==NULL){
                return NULL;
        }
	struct node *temp = malloc_fptr(sizeof(struct node));
	temp->data=data;

	//Case 1: Empty linked_list
	//
	if(ll->head==NULL) {
		temp->next=NULL;
		ll->head=temp;
		ll->size+=1;
		return true;
	}

	//Case 2: Non Empty linked_list
	//
	temp->next=ll->head;
	ll->head=temp;
	ll->size+=1;
	return true;
}

// Inserts an element at a specified index in the linked_list.
// \param ll    : Pointer to linked_list.
// \param index : Index to insert data at.
// \param data  : Data to insert.
// Returns TRUE on success, FALSE otherwise.
//

bool linked_list_insert(struct linked_list *ll,	size_t index,unsigned int data) {
	
	if(ll==NULL) {
		return false;
	}

	if(ll->head==NULL && index>0) {
                return false;
        }

	if(malloc_fptr==NULL){
                return false;
        }

	//Case 1: Insertion at index 0 in case of an empty linked list
	//
	if(index==0 || ll->head==NULL) {
		return linked_list_insert_front(ll,data);
        }
	
	//Case 2: If the index specified is greater than ll->size,
	//        the default behaviour would be to insert the new element at the end of the linked list
	//
	if(index>ll->size){
		return linked_list_insert_end(ll,data);
	}
	
	size_t tempindex=1;
	struct node *curr=ll->head;
	struct node *before=ll->head;
	struct node *temp=malloc_fptr(sizeof(struct node));
	if(!temp){
		return false; //Memory allocation failure
	}
	temp->data=data;
	temp->next=NULL;
	while(tempindex<index+1) {
		if(curr->next==NULL) { 
			//Case 3: Handling insertion if we reach the end of linked list
			linked_list_insert_end(ll,data); 
									
			return true;
		}
		//Case 4 Normal Insertion
		//
		before=curr;
		curr=curr->next;
		tempindex+=1;
	}
	before->next=temp;
	temp->next=curr;
	ll->size+=1;
	return true;
}

// Finds the first occurrence of data and returns its index.
// \param ll   : Pointer to linked_list.
// \param data : Data to find.
// Returns index of the first index with that data, SIZE_MAX otherwise.
//

size_t linked_list_find(struct linked_list *ll,unsigned int data) {
	
	if(ll==NULL) {
		return SIZE_MAX;
	}
	if(ll->head==NULL) {
		return SIZE_MAX;
	}
	struct iterator *iter=linked_list_create_iterator(ll,0);
	if(iter==NULL){
		return SIZE_MAX;
	}
	while(iter->current_node!=NULL) {
		if(iter->data==data) {
			return iter->current_index;
		}
		linked_list_iterate(iter);
	}
	return SIZE_MAX;
}

// Removes a node from the linked_list at a specific index.
// \param ll    : Pointer to linked_list.
// \param index : Index to remove node.
// Returns TRUE on success, FALSE otherwise.
//

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

	//Case 1: Invalid index size
	//
	if(index>ll->size){ 
		return false;
	}


	struct node *curr=ll->head;	
	struct node *before=malloc_fptr(sizeof(struct node));
	
	//Case 1 Removal in case of a single element in the linked list
	//
	if(index==0 && curr->next==NULL) {
		free_fptr(curr);
                ll->head=NULL;
		ll->size-=1;
                return true;
        }
	//Case 2 Removal of the initial element in a linked list
	//
	if(index==0) {
		before=curr->next;
		free_fptr(curr);
		ll->head=before;
		ll->size-=1;
		return true;
	}
	
	
	
	while(index>0) {
		/*if(curr==NULL) { 
			return false;
		}*/
		before=curr;
		curr=curr->next;
		index-=1;
	}
	before->next=curr->next;
	free_fptr(curr);
	ll->size-=1;
	return true;
}

// Creates an iterator struct at a particular index.
// \param linked_list : Pointer to linked_list.
// \param index       : Index of the linked list to start at.
// Returns pointer to an iterator on success, NULL otherwise.
//

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

// Deletes an iterator struct.
// \param iterator : Iterator to delete.
// Returns TRUE on success, FALSE otherwise.
//

bool linked_list_delete_iterator(struct iterator *iter) {
	if(iter==NULL) {
		return false;
	}
	//free_fptr(iter->current_index);
	free_fptr(iter);
	return true;
}

// Iterates to the next node in the linked_list.
// \param iterator: Iterator to iterate on.
// Returns TRUE when next node is present, FALSE once end of list is reached.
//

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

// Registers malloc() function.
// \param malloc : Function pointer to malloc()-like function.
// Returns TRUE on success, FALSE otherwise.
//

bool linked_list_register_malloc(void *(*malloc)(size_t)) {
	if(malloc==NULL) {
		return false;
	}
	malloc_fptr=malloc;
	return true; //Success
}

// Registers free() function.
// \param free : Function pointer to free()-like function.
// Returns TRUE on success, FALSE otherwise.
//

bool linked_list_register_free(void (*free)(void*)){
	if(free==NULL) {
		return false;
	}
	free_fptr=free;
	return true;
}
