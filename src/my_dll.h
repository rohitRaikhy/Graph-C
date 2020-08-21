// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
    void* data;
    struct node* next;
    struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
    int count;        // count keeps track of how many items are in the DLL.
    node_t* head;        // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.
    dll_t* myDLL= malloc(sizeof(dll_t));
    myDLL->count =0;
    myDLL->head = NULL;
    myDLL->tail = NULL;
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
// Returns -1 if the dll is NULL.
int dll_empty(dll_t* l){

	if(l == NULL) {
		return -1;
	}
	else if(l -> count == 0){
		return 1;
	}
	else {
		return 0;
	}
}
		

// push a new item to the front of the DLL ( before the first node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
   
	if(l == NULL) {
		return -1;
	}

	node_t* new_node = malloc(sizeof(node_t));
	
	if(new_node == NULL) {
		return 0;
	}	

	new_node -> data = item;
	new_node -> next = l -> head;
	new_node -> previous = NULL;

	if(l -> count == 0) {
		l -> head = new_node;
		l -> tail = new_node;
		l -> count += 1;
		return 1;
	}

	l -> head -> previous = new_node;
	l -> head = new_node;
	l -> count += 1;

	return 1;
}


// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	
	if(l == NULL) {
        	return -1;
	}
	
	node_t* new_node = malloc(sizeof(node_t));
	
	if(new_node == NULL) {
		return 0;
	}
	
	new_node -> data = item;
	new_node -> next = NULL;
	new_node -> previous = l -> tail;
	
	if(l -> count == 0) {
		l -> head = new_node;
		l -> tail = new_node;
		l -> count += 1;
		return 1;
	 }
	l -> tail -> next = new_node;	
	l -> tail = new_node;
	l -> count += 1;
	
	return 1;

}

// Returns the first item in the DLL and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* t){
	

	void* value;

	if(t == NULL) {
		return NULL;
	}

	else if(t -> count == 0) {
		return NULL;
	} else {

	 	value = t -> head ->  data;
		if(t -> count == 1) {
			t -> count -= 1;
			return value;
		}
		node_t* temp = t -> head;		
		t -> head = temp -> next;
		temp -> next -> previous = NULL;
		t -> count -= 1;
		free(temp);
		return value;
	}
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* t){
	
	if(t == NULL) {
		return NULL;
	}
	else if(t -> count == 0) {
		return NULL;
	}
	else {
		void* value = t -> tail -> data;
		if(t -> count == 1){
			t -> count -= 1;
			return value;
		}
		node_t* temp = t -> tail;
		t -> tail = temp -> previous;
		temp -> previous -> next = NULL;
		t -> count -= 1;
		free(temp);
		return value;
	} 	
}

// Inserts a new node before the node at the specified position.
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
// Returns -1 if the list is NULL
int dll_insert(dll_t* l, int pos, void* item){
       	
	 
        if(l == NULL) {
		return -1;
	}
	
	else if(pos == l -> count) {
		dll_push_back(l, item);
		return 1;
	} 
	
	else {
		if(pos < 0 || pos > l -> count) {
		return 0;
		} else { 
			if(pos == 0) {
				dll_push_front(l, item);
				return 1;
			}
			node_t* new_node = malloc(sizeof(node_t));
			if(new_node == NULL){
				return 0;
			}
			node_t* temp = l -> head; 
			int i = 0;
			while(i < pos) {
				temp = temp -> next; 
				i++;
			} 	
			new_node -> data = item;
			new_node -> next = temp;
			new_node -> previous = temp -> previous;
			new_node -> previous -> next = new_node;
			new_node -> next -> previous = new_node; 

			l -> count += 1;
			return 1;		 
		}
	}
}	

// Returns the item at position pos starting at 0 ( 0 being the first item )
//  (does not remove the item)
// Retruns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	
	if(l == NULL){	
		return NULL;
	}
	else if(pos < 0 || pos > l -> count){
		return NULL;
	} else{ 
		if(pos == 0) {
			return l  -> head -> data;
		}
		else if(pos == l -> count -1){	
			return l -> tail -> data; 
		} 
		else{
			node_t* temp = l -> head;
			int i = 0;
			while(i < pos){
				temp = temp -> next;
				i++;
			}
		return temp -> data;
		}	
 	}	        
}

// Removes the item at position pos starting at 0 (0 being the first item )
// Retruns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns NULL if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
        
      	if(l == NULL){
		return NULL;
	}
	else if(pos < 0 || pos > l -> count -1){
		return NULL;
	}
	else if(pos == 0 && l -> count == 1) {
		void* item = l -> head -> data;
		free(l -> head);
		l -> head = NULL;
		l -> tail = NULL;
		l -> count -= 1;
		return item;
	} 
	else{
		// remove at head. 
		if(pos == 0){
			node_t* temp = l -> head;
			l -> head -> next -> previous = NULL;
			void* item = l -> head -> data;
			temp = l -> head -> next;
			free(l -> head);
			l -> head = temp;
			l -> count -= 1;
			return item;
		}
		// remove at tail.
		else if(pos == l -> count - 1){
			node_t* temp = l -> tail;
			l -> tail -> previous -> next = NULL;
			void* item = l ->tail -> data;
			temp = l -> tail -> previous;
			free(l -> tail);
			l -> tail =  temp;
			l -> count -= 1;	
			return item;

		} else {
			node_t* temp = l -> head;
			int i = 0;
			while(i<pos){
				temp = temp -> next;
				i++;
			}
			void* item = temp -> data;	
			temp -> previous -> next = temp -> next;
			temp -> next -> previous = temp -> previous;
			free(temp);
			l -> count -= 1;	
			return item;
		}
	} 
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* t){
    
        if(t == NULL) {
		return -1;
	}
	else {
		return t -> count;	
	}  
}




// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
	
	if (t == NULL){
		return;
	} 
	node_t* temp_node;
	// changed here
	
	while(t -> head != NULL){
		temp_node = t -> head;
		t -> head = t -> head -> next;
		free(temp_node);
	}
	free(t);	
}



#endif
