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
	l1->tail=NULL;
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
	if(free_fptr==NULL) {
		return false;
        }

	struct node *curr=ll->head;
	struct node *temp;
	while(curr!=ll->tail) {
		temp=curr;
		curr=curr->next;
		free_fptr(temp);
		curr->prev=NULL;
		ll->size-=1;
	}
	free(ll->tail); 
	free_fptr(ll);
	ll=NULL;
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
	temp->prev=NULL;
	//Case 1: Empty linked_list
	//
	if(ll->head==NULL) {
		ll->tail=temp;
		ll->head=temp;
		ll->size+=1;
		return true;
	}
	//struct node *curr=ll->head;

	//Case 2 Non Empty Linked Lists
	//
	//while(curr->next!=NULL) { 
	//	curr=curr->next;
	//}
	//curr->next=temp;
	//
	//
	//O(k) time complexity
	ll->tail->next=temp;
	temp->prev=ll->tail;
	ll->tail=temp;
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
		temp->prev=NULL;
		ll->head=temp;
		ll->tail=temp;
		ll->size+=1;
		return true;
	}

	//Case 2: Non Empty linked_list
	//
	ll->head->prev=temp;
	temp->next=ll->head;
	temp->prev=NULL;
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
	if(index>=ll->size){
		return linked_list_insert_end(ll,data);
	}

	struct node *temp=malloc_fptr(sizeof(struct node));
        if(!temp){
                return false; //Memory allocation failure
        }
        temp->data=data;
        temp->next=NULL;

	size_t tmpSize = (ll->size/2);

	//Case 3:Trying to optimize my existing O(n) approach by iterating from the ll->head if index <=(ll->size/2)

	if(index<=tmpSize) {
	size_t tempindex=1;
	struct node *curr=ll->head;
	struct node *before=ll->head;
	while(tempindex<index+1) {
		/*if(curr->next==NULL) { 
			//Case 3: Handling insertion if we reach the end of linked list
			linked_list_insert_end(ll,data); 
			free_fptr(temp);
			temp=NULL;			
			return true;
		}*/
		//
		//
		before=curr;
		curr=curr->next;
		tempindex+=1;
	}
	before->next=temp;
	temp->next=curr;
	temp->prev=before;
	curr->prev=temp;
	ll->size+=1;
	}

	//Case 4:Trying to optimize my existing O(n) approach by iterating from ll->tail if index >(ll/size/2)

	else {
		size_t tempindex=ll->size;
		struct node *curr=ll->tail;
		struct node *before=ll->tail;
		while(tempindex>index) {
			/*if(curr->prev==NULL) {
				linked_list_insert_front(ll,data);
				free_fptr(temp);
				temp=NULL;
				return true;
			}*/
			
			curr=before;
			before=before->prev;
			tempindex-=1;
		}
		before->next=temp;
		temp->prev=before;
		temp->next=curr;
		curr->prev=temp;
		ll->size+=1;
	}
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
			size_t tempidx = iter->current_index;
			free_fptr(iter); //dangling ptr
                        iter=NULL;
			return tempidx;
		}
		linked_list_iterate(iter);
	}
	free_fptr(iter);
	iter=NULL;
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
	if(free_fptr==NULL) {
		return NULL;
	}

	//Case 1: Invalid index size
	//
	if(index>=ll->size){ 
		return false;
	}


	struct node *curr=ll->head;
	//Case 2 Removal in case of a single element in the linked list
	//
	if(index==0 && curr->next==NULL) {
		free_fptr(curr);
                ll->head=NULL;
		ll->tail=NULL;
		ll->size-=1;
                return true;
        }
	//Case 3 Removal of the initial element in a linked list
	//
	struct node *before;
	if(index==0 && curr->next!=NULL) {
		before=curr;
		curr=curr->next;
		free_fptr(before);
		before=NULL;
		curr->prev=NULL;
		ll->head=curr;
		ll->size-=1;
		return true;
	}
	size_t tmpSize= ll->size/2;
	size_t tmpIndex=ll->size-1;

	
	//Case 4: Trying to optimize and speedup my existing O(n) approach by iterating from ll->head if target index if less than or equal to ll->size/2
	if(index<=tmpSize) {
		while(index>0) {
			/*if(curr==NULL) { 
			 * return false;
			 * }*/
			before=curr;
			curr=curr->next;
			index-=1;
		}
		before->next=curr->next;
		curr->next->prev=before;
		free_fptr(curr);
		ll->tail=before->next;
		ll->size-=1;
	}
	//Case 5:Iterate from ll->tail if index >(ll->size/2)
	//
	else {
		curr=ll->tail;
		before=curr->prev;
		while(tmpIndex>index) {
				curr=before;
				before=curr->prev;
				tmpIndex-=1;
		}
		//before->next=curr->next;i
		//curr->next->prev=before;
		//
		if(curr->next) {
			before->next=curr->next;
			ll->tail=before->next;
		}
		else { 
			//before->next=NULL;
			//
			before->next=NULL;
			ll->tail=before;
			//before->next=curr->next;

		}
		free_fptr(curr);
		curr=NULL;
		ll->size-=1;
	}
	//free_fptr(before); //dangling pointer
	//before=NULL;
	//free_fptr(malloc_fptr);
	//malloc_fptr=NULL;
	//
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
		free_fptr(i1);
		i1=NULL;
		return NULL;
	}
	struct node *curr=ll->head;
	i1->ll=ll;
	i1->current_index=index;
	i1->data=curr->data;
	i1->current_node=ll->head;
	//free_fptr(malloc_fptr);
   	//malloc_fptr=NULL;
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
