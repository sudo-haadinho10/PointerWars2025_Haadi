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
bool linked_list_register_malloc(void * (*malloc)(size_t));
bool linked_list_register_free(void (*free)(void*));

#endif

