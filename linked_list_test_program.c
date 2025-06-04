#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"

//#  the pound sign means to expand this parameter to the literal text of the argument that was passed to the macro.

#define TEST(x) printf("Running test " #x "\n"); fflush(stdout);
#define SUBTEST(x) printf("   Executing subtest " #x "\n"); fflush(stdout); \
		   alarm(1);
#define FAIL(cond,msg) if (cond) {\
	printf("   FAIL! "); \
	printf(#msg "\n"); \
	exit(-1);

#define PASS(x) printf("PASS!\n"); alarm(0);

bool instrumented_malloc_fail_next             = false;
bool instrumented_malloc_last_alloc_successful = false;

void *instrumented_malloc(size_t size) {
	if(instrumented_malloc_fail_next) {
		instrumented_malloc_fail_next =false;
		instrumented_malloc_last_alloc_successful=false;
		return NULL;
	}

	void *ptr = malloc(size);
	instrumented_malloc_last_alloc_successful=(ptr!=NULL);

	return ptr;
}

void instrumented_free(void * addr){
	if(addr==NULL){
		return;
	}
	free(addr);
}

void gracefully_exit_on_suspected_infinite_loop(int signal_number) {
	const char* err_msg = "        Likely stuck in infinite loop! Exiting.\n";
	ssize_t retval =write(STDOUT_FILENO,err_msg,strlen(err_msg));
	fflush(stdout);
	
	 // We really don't care about whether write() succeeded or failed
    	// or whether a partial write occurred. Further, we only install
    	// this function to one signal handler, so we can ignore that as well.
    	// -Wall
	
	(void)retval;
	(void)signal_number; 	
	
	exit(1);
}	

/*void check_empty_list_properties(void) {
	TEST(check_empty_list_properties);
	SUBTEST(linked_list_create);
	struct linked_list *ll=linked_list_create();


    	// Sanity check that linked_list_create() works on memory allocation
    	// success.
	FAIL((instrumented_malloc_last_alloc_successful && (ll==NULL)),
			"linked_list_create() failed when malloc() returned a valid pointer")	
	//Check invariant that head is null when empty.
	//
	FAIL((ll->head!=NULL),
			"ll->head is non-null in empty linked list");

	//linked_list_delete(ll);
	 if(linked_list_delete(ll)){
                printf("SUCCESS\n");
        }
}*/



int main(void) {
	//Set up signal handler for catching infinite loops.
	//
	signal(SIGALRM,gracefully_exit_on_suspected_infinite_loop);
	// Setup instrumented memory allocation/deallocation.
	
	if(linked_list_register_malloc(&instrumented_malloc)){
		fprintf(stderr, "Failed to register instrumented malloc\n");	
		return 1;
	}
	if(linked_list_register_free(&instrumented_free)){
		fprintf(stderr,"Failed to register instrumented free\n");
		return 1;
	}
	
	
	struct linked_list *l1=linked_list_create();

	if(l1->head==NULL){
		printf("success\n");
	}

	// Add a node
    struct node *new_node = instrumented_malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Failed to allocate new node\n");
        linked_list_delete(l1);
        return 1;
    }
    new_node->data = 5;
    new_node->next = NULL;
    l1->head=new_node ;

    //linked_list_delete(ll);
         if(linked_list_delete(l1)){
                printf("SUCCESS\n");
        }
    

  
	
   //     check_empty_list_properties();
	//check_insertion_functionality();
	return 0;
}

