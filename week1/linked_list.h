#ifndef LINKED_LIST_H_
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

//linked_list structure declaration

struct node;
struct linked_list {
	struct node * head;
	size_t size;
};

struct node {
	struct node *next;
	unsigned int data;
};

struct iterator {
	struct linked_list *ll;
	struct node * current_node;
	size_t current_index; //stddef.h
	unsigned int data;
};

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

#endif

