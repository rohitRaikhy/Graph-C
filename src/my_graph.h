// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
}graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
}graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

//Returns the node pointer if the node exists.
//Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
	if(g == NULL) {
		return NULL;
	} 
 		
	node_t* itr = g -> nodes -> head; 
	while(itr != NULL) {
		graph_node_t* firstGraphNode = itr -> data;
		if(firstGraphNode -> data == value) {
			return firstGraphNode;
		} else {
			itr = itr -> next;
		} 	
	}
	return NULL;
}

graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

//Returns 1 on scucess
//Returns 0 on failure ( or if the node already exists )
//Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return -1;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;
    
    return 1;
}


// add another helper function to remove from dll
void remove_from_dll(dll_t* l, int value) {
	
	int index = 0;
	node_t* itr = l -> head;

	if(l -> count == 0) {
		return;
	}

	while(itr != NULL) {
		graph_node_t* gnode = itr -> data; 	
		if(gnode -> data == value) {
			dll_remove(l, index);
			return;
		} else {
			itr = itr -> next;
			index += 1;
		}

	}
}


void remove_inNeighbors(graph_t* g, int value) {
	if(g == NULL){
		return;
	} 

	node_t* itr = g -> nodes -> head;
	while(itr != NULL) {
		graph_node_t* firstNode = itr -> data;
		dll_t* itrInNeighbors = firstNode -> inNeighbors;
		remove_from_dll(itrInNeighbors, value);
		itr = itr -> next;	
	} 	
}
	


void remove_outNeighbors(graph_t* g, int value) {
	if(g == NULL){
		return;
	} 

	node_t* itr = g -> nodes -> head;
	while(itr != NULL) {
		graph_node_t* firstNode = itr -> data;
		dll_t* itrOutNeighbors = firstNode -> outNeighbors;
		remove_from_dll(itrOutNeighbors, value);
		itr = itr -> next;	
	} 	
}




//Returns 1 on success
//Returns 0 on failure ( or if the node doesn't exist )
//Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    //The function removes the node from the graph along with any edges associated with it.
    //That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
	if(g == NULL) {
		return -1;
	}
	remove_inNeighbors(g, value);
	remove_outNeighbors(g, value);
	
	node_t* itr = g -> nodes -> head;
	int index = 0;
	while(itr != NULL) {
		
		graph_node_t* firstNode = itr -> data;
		if(firstNode -> data == value) {
			dll_remove(g -> nodes, index);
			g -> numNodes -= 1;
			return 1;
		
		} else {
			itr = itr -> next;
			index += 1;
		}
	}
	return 0;
}
	

//Returns 1 on success
//Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
//Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    //The function adds an edge from source to destination but not the other way.
    //Make sure you are not adding the same edge multiple times.
        //Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    //Source will be an in neighbor of destination.
 	  
	if(g == NULL) {
		return -1;
	}
	graph_node_t* findSource = find_node(g, source);
	graph_node_t* findDestination = find_node(g, destination);
	
	if(findSource == NULL) {
		return 0;
	} 
	if(findDestination == NULL) {
		return 0;
	}
	
	node_t* itr = findSource -> outNeighbors -> head;

	while(itr != NULL){
		graph_node_t* firstNode = itr -> data;
		if(firstNode -> data == findDestination -> data) {
			return 0;
		} else { 
			itr = itr -> next;
		}
	}			
	dll_push_back(findSource -> outNeighbors, findDestination);
	node_t* itr2 = findDestination -> inNeighbors -> head;

	while(itr != NULL){
		graph_node_t* firstNode = itr2 -> data;
		if(firstNode -> data == findSource -> data) {
			return 0;
		} else { 
			itr2 = itr2 -> next;
		}
	}
	dll_push_back(findDestination -> inNeighbors, findSource);
	g -> numEdges += 1;
	return 1;		
}
	


//Returns 1 on success
//Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
//Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
   	if(g == NULL) {
		return -1;
	}
	graph_node_t* findSource = find_node(g, source);
	graph_node_t* findDestination = find_node(g, destination);
	
	if(findSource == NULL) {
		return 0;
	} 
	if(findDestination == NULL) {
		return 0;
	}
	int index = 0;

	node_t* itr = findSource -> outNeighbors -> head;

	while(itr != NULL){
		graph_node_t* firstNode = itr -> data;
		if(firstNode -> data == findDestination -> data) {
			dll_remove(findSource -> outNeighbors, index);
			break;
		} else { 
			itr = itr -> next;
			index += 1;
		
		}
	}
	
	int index2 = 0;

	node_t* itr2 = findDestination -> inNeighbors -> head;

	while(itr2 != NULL){
		graph_node_t* firstNode = itr2 -> data;
		if(firstNode -> data == source) {
			
			dll_remove(findDestination -> inNeighbors, index);
			return 1;
		} else { 
			itr2 = itr2 -> next;
			index2 += 1;
		}

	} 
	return 0;	
}

//Returns 1 on success
//Returns 0 on failure ( or if the source or destination nodes don't exist )
//Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destintaion){

	if(g == NULL) {
		return -1;
	}
		
	graph_node_t* findSource = find_node(g, source);
	graph_node_t* findDestination = find_node(g, destintaion);
	
	if(findSource == NULL) {
		return 0;
	} 
	if(findDestination == NULL) {
		return 0;
	}

	node_t* itr = findSource -> outNeighbors -> head;

	while(itr != NULL){
		graph_node_t* firstNode = itr -> data;
		if(firstNode -> data == findDestination -> data) {
			return 1;
		} else { 
			itr = itr -> next;
		}
	}
	return 0;
}

//Returns dll_t* of all the in neighbors of this node.
//Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){

	if(g == NULL) {
    		return NULL;
	} 

	graph_node_t* findNode = find_node(g, value);

	if(findNode == NULL) {
		return NULL;
	} 
	
	return(findNode -> inNeighbors);
}

//Returns the number of in neighbors of this node.
//Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
	
	if(g == NULL) {
		return -1;
	}

	graph_node_t* node = find_node(g, value);	
	if(node == NULL) {
		return -1;
	}

	return node -> inNeighbors -> count;
}


//Returns dll_t* of all the out neighbors of this node.
//Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
	
	if(g == NULL) {
    		return NULL;
	} 

	graph_node_t* findNode = find_node(g, value);

	if(findNode == NULL) {
		return NULL;
	} 
	
	return(findNode -> outNeighbors);
}


//Returns the number of out neighbors of this node.
//Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
    	
	if(g == NULL) {
		return -1;
	}

	graph_node_t* node = find_node(g, value);	
	if(node == NULL) {
		return -1;
	}
	return node -> outNeighbors -> count; 
}



// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
 	if(g == NULL) {
		return -1;
	} 
	return g -> numNodes;	
}


// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    
	if(g == NULL) {
		return -1;
	}
	return g -> numEdges;		
}

//Returns 1 if reachable
//Returns 0 if not reachable.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int is_reachable(graph_t * g, int source, int dest){
    //Implement using BFS.
    //Make sure you don't get stuck into an infinite loop.
 	
	if(g == NULL ){	
		return -1;
	}   
	
	
	dll_t* queue = create_dll();
	graph_node_t* findSource = find_node(g, source);
	graph_node_t* findDest = find_node(g, dest);
	
	if(findSource == NULL) {
	
		free(queue);
		return -1;
	} 

	if(findDest == NULL) {
	
		free(queue);
		return -1;
	}

	node_t* outNeigh = findSource -> outNeighbors -> head;
	// to auto set to 0 values
	int INSEENARRAY [g -> numNodes];

	while(outNeigh != NULL) {
		int inSeenIndex = 0;
		graph_node_t* node = outNeigh -> data;
		INSEENARRAY[inSeenIndex] = node -> data;
		inSeenIndex += 1;
		dll_push_back(queue, node);
		outNeigh = outNeigh -> next;
	}
	
	while(dll_size(queue) > 0) {
	
		graph_node_t* getNode = dll_pop_front(queue);
		
		if(getNode -> data == findDest -> data) {
			
			free(queue);
			return 1;
		} else {
			if(getNode -> outNeighbors -> count > 0){ 
				node_t* outNeigh2 = getNode -> outNeighbors -> head;
				int inSeen = 0;
				int index = 0;
				while(outNeigh2 != NULL) {
					graph_node_t* getNode2 = outNeigh2 -> data;
					int i;
					int sizeArray = (sizeof(INSEENARRAY) / sizeof(INSEENARRAY[0]));
					for(i = 0; i <= sizeArray; i++) {
						if(getNode2 -> data == INSEENARRAY[i]) {
							inSeen = 1;
							break;
						} else {
							index += 1;
							inSeen = 0;
						}
					}
					if(inSeen == 0) {
						dll_push_back(queue, getNode2);
						INSEENARRAY[index] = getNode2 -> data;
						outNeigh2 = outNeigh2 -> next;
					} else {
						outNeigh2 = outNeigh2 -> next;
					}
				}		
			}
		}
	}
	free(queue);
	return 0;
}

//Returns 1 if the graph has a cycle.
//Returns 0 if the graph doesn't have a cycle.
//Returns -1 if the graph is NULL or if either of the nodes doesn't exist.
int has_cycle(graph_t * g){

	
	if(g == NULL ){	
		return -1;
	}   
	
	
	dll_t* queue = create_dll();
	
	graph_node_t* startNode = g -> nodes -> head -> data;
	node_t* outNeigh =  startNode -> outNeighbors -> head;
	// to auto set to 0 values
	int INSEENARRAY [g -> numNodes];

	while(outNeigh != NULL) {
		int inSeenIndex = 0;
		graph_node_t* node = outNeigh -> data;
		INSEENARRAY[inSeenIndex] = node -> data;
		inSeenIndex += 1;
		dll_push_back(queue, node);
		outNeigh = outNeigh -> next;
	}
	
	while(dll_size(queue) > 0) {
	
		graph_node_t* getNode = dll_pop_back(queue);
	
		if(getNode -> outNeighbors -> count > 0){ 
			node_t* outNeigh2 = getNode -> outNeighbors -> head;
			int inSeen = 0;
			int index = 0;
			while(outNeigh2 != NULL) {
				graph_node_t* getNode2 = outNeigh2 -> data;
				int i;
				int sizeArray = (sizeof(INSEENARRAY) / sizeof(INSEENARRAY[0]));
				for(i = 0; i <= sizeArray; i++) {
					if(getNode2 -> data == INSEENARRAY[i]) {
						inSeen = 1;
						break;
					} else {
						index += 1;
						inSeen = 0;
					}
				}
				if(inSeen == 0) {
					dll_push_back(queue, getNode2);
					INSEENARRAY[index] = getNode2 -> data;
					outNeigh2 = outNeigh2 -> next;
				} else {
					free(queue);
					return 1;
				}
			}		
		}
	}
	free(queue);
	return 0;
}

//Prints all the nodes from source to destination ( including the source and destination),
//i.e. print_path(1,5) => 1 2 3 4 5
//otherwise it prints "path does not exit" or if source or dest nodes do not exist or if the graph is NULL.
void print_path(graph_t * g, int source, int dest){

     if(g == NULL) {
    		printf("Path does not exist\n");
     } 

     graph_node_t* sourceNode = find_node(g, source);
     graph_node_t* destNode = find_node(g, dest);
	
     if(sourceNode == NULL || destNode == NULL) {
	printf("Path does not exist\n");
     } 

     if(is_reachable(g, source, dest) == 1) {
		

	dll_t* queue = create_dll();
	
	graph_node_t* startNode = g -> nodes -> head -> data;
	node_t* outNeigh =  startNode -> outNeighbors -> head;

	int INSEENARRAY [g -> numNodes];

	while(outNeigh != NULL) {
		int inSeenIndex = 0;
		graph_node_t* node = sourceNode;
		INSEENARRAY[inSeenIndex] = node -> data;
		inSeenIndex += 1;
		dll_push_back(queue, node);
		outNeigh = outNeigh -> next;
	}
	
	while(dll_size(queue) > 0) {
	
		graph_node_t* getNode = dll_pop_back(queue);
		printf("-%d", getNode -> data);
		if(getNode -> data == destNode -> data) { 
			free(queue);
			return;
		}
		if(getNode -> outNeighbors -> count > 0){ 
			node_t* outNeigh2 = getNode -> outNeighbors -> head;
			int inSeen = 0;
			int index = 0;
			while(outNeigh2 != NULL) {
				graph_node_t* getNode2 = outNeigh2 -> data;
				int i;
				int sizeArray = (sizeof(INSEENARRAY) / sizeof(INSEENARRAY[0]));
				for(i = 0; i <= sizeArray; i++) {
					if(getNode2 -> data == INSEENARRAY[i]) {
						inSeen = 1;
					} else {
						index += 1;
						inSeen = 0;
					}
				}
				if(inSeen == 0) {
					dll_push_back(queue, getNode2);
					INSEENARRAY[index] = getNode2 -> data;
					outNeigh2 = outNeigh2 -> next;
				} else {
					outNeigh2 = outNeigh2 -> next;
				}
			}		
		}
	}
	free(queue);
	return;
	}
}




// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the proram terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){

 	if(g != NULL){
        node_t* temp = g->nodes->head;
        while(temp != NULL){
            graph_node_t* curr = temp->data;
            temp = temp->next;
            free_dll(curr->inNeighbors);
            free_dll(curr->outNeighbors);
            free(curr);
            
        }    
        free_dll(g->nodes);
        free(g);
    }
}

#endif
