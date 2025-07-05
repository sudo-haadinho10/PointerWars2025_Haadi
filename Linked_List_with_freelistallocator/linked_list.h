#ifndef LINKED_LIST_H_
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//#define SIZE (size_t) 20

//linked_list structure declaration

//#define ALLOC_HEADER_SZ offsetof(node,block) //returns offset of the field member from the start of the structure type.


//#ifndef align_up
//	#define align_up(num,align) (((num)+((align)-1)) & ~((align)-1))


/*struct memorypool {
	struct node *pool_start; //Pointer to the big block allocated
	struct node *free_list_head;
	size_t capacity; //total number of nodes in our pool
};*/

//static struct node *free_list;

struct linked_list {
	struct node * head;
	size_t size;
	struct node *tail;	
	//struct memorypool *pool; //head of the free_list (freed node pointers)
	//
}; // Defines the struct with its members

struct node {
	struct node *next;
	unsigned int data;
	struct node *prev;
	size_t size; //Size of the block (including header)
};

struct iterator {
	struct linked_list *ll;
 	struct node * current_node;
	size_t current_index; //stddef.h
	unsigned int data;
};


//struct memorypool *create_memory_pool(size_t num_nodes);
struct node *linked_list_create_node(void);
bool linked_list_delete_node(struct node *node);
void free_list_cleanup(void);

struct linked_list * linked_list_create(void);
bool linked_list_delete(struct linked_list * ll);
size_t linked_list_size(struct linked_list *ll);

struct iterator * linked_list_create_iterator(struct linked_list *ll,size_t index);
bool linked_list_delete_iterator(struct iterator * iter);
bool linked_list_iterate(struct iterator * iter);

bool linked_list_insert_end(struct linked_list *ll,unsigned int data);
bool linked_list_insert_front(struct linked_list *ll,unsigned int data);

bool linked_list_insert(struct linked_list *ll,size_t index,unsigned int data);
size_t linked_list_find(struct linked_list *ll,unsigned int data);
bool linked_list_remove(struct linked_list *ll,size_t index);

bool linked_list_register_malloc(void * (*malloc)(size_t));
bool linked_list_register_free(void (*free)(void*));

//ignore
void malloc_addblock(void *addr,size_t size);


#endif

