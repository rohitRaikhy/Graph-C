// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


void printNodes(graph_t* g) {
	

	node_t* itr = g -> nodes -> head;
	while(itr != NULL) {
		graph_node_t* firstNode = itr -> data;
		printf("value in graph: %d\n", firstNode -> data);
		itr = itr -> next;
	}
}


//unitTest1
//test to see create graph 
void unitTest1() {
	graph_t* graph = create_graph();
	printf("numEdges, expected = 0, actual = %d\n", graph -> numEdges);
	printf("numNodes, expected = 0, actual = %d\n", graph -> numNodes);
	
	free_graph(graph);
}

// unitTest2
// test of add node and get number of nodes
void unitTest2() {

	graph_t * graph = create_graph();
       
	printf("total nodes, expected = %d, actual = %d\n", 0, graph_num_nodes(graph));    		
    	graph_add_node(graph, 1);
	printf("total nodes, expected = %d, actual = %d\n", 1, graph_num_nodes(graph));
 			
    	graph_add_node(graph, 1);
	printf("total nodes, expected = %d, actual = %d\n", 1, graph_num_nodes(graph));
    	
    	graph_add_node(graph, 2);
    	printf("total nodes, expected = %d, actual = %d\n", 2, graph_num_nodes(graph));

	free_graph(graph);
}


//unitTest3 
//test to remove a node and get num
void unitTest3() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 5);

//	graph_remove_node(graph, 3);
	printf("total nodes, expected = %d, actual = %d\n", 2, graph_num_nodes(graph));
//	free_graph(graph);
}
// havent finshed testtingyet 
//unitTest4 
//test to remove a node and get num
void unitTest4() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);

	graph_node_t* findOne = find_node(graph, 1);
	graph_node_t* findTwo = find_node(graph, 2);
	printf("total nodes, expected = %d, actual = %d\n", 2, graph_num_nodes(graph));
	printf("findOne value, expected = %d, actual = %d\n", 1, findOne -> data);
	printf("findTwo value, expected = %d, actual = %d\n", 2, findTwo -> data);	

	free_graph(graph);
}

int printOutNeighbors(graph_t* g, int source) {
	
	graph_node_t* findNode = find_node(g, source);

	if(findNode -> outNeighbors -> count == 0) {
		return 0;
	}
	
	node_t* itr = findNode -> outNeighbors -> head;
	while(itr != NULL) {
		graph_node_t* firstNode = itr -> data;
		printf("Value in outNeighbors: %d\n", firstNode -> data);
		itr = itr -> next;
	}
}


int printInNeighbors(graph_t* g, int destination) {
	
	graph_node_t* findNode = find_node(g, destination);

	if(findNode -> inNeighbors -> count == 0) {
		return 0;
	}
	node_t* itr = findNode -> inNeighbors -> head;
	while(itr != NULL) {
		graph_node_t* firstNode = itr -> data;
		printf("Value in inNeighbors: %d\n", firstNode -> data);
		itr = itr -> next;
	}
}
	


//unitTest5 
//test to add neighbours
void unitTest5() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);

	graph_node_t* findOne = find_node(graph, 1);
	graph_node_t* findTwo = find_node(graph, 2);
	printf("total nodes, expected = %d, actual = %d\n", 2, graph_num_nodes(graph));
	printf("findOne value, expected = %d, actual = %d\n", 1, findOne -> data);
	printf("findTwo value, expected = %d, actual = %d\n", 2, findTwo -> data);

	printf("........\n");	

	graph_add_edge(graph, 1, 2);
	printf("Outneighbors in node 1, expected: %d, actual: %d\n", 1, findOne -> outNeighbors -> count);	
	printOutNeighbors(graph, 1);	
	printf("inNeighbors in node 2, expected: %d, actual: %d\n", 1, findOne -> outNeighbors -> count);	
	printInNeighbors(graph, 2);

	printf(".... check adding same edge again \n");
	
	int result = graph_add_edge(graph, 1, 2);
	printf("try adding the same edge again, expected: %d, actual: %d\n", 0, result);
	printf("Outneighbors in node 1, expected: %d, actual: %d\n", 1, findOne -> outNeighbors -> count);	
	printOutNeighbors(graph, 1);	
	printf("inNeighbors in node 2, expected: %d, actual: %d\n", 1, findOne -> outNeighbors -> count);	
	printInNeighbors(graph, 2);

	free_graph(graph);
}


//unitTest6 
//test to null add edge
void unitTest6() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	
	int result = graph_add_edge(graph, 1, 3);	

	printf("total nodes, expected = %d, actual = %d\n", 0, result);

	free_graph(graph);
}

//unitTest7 
//test remove node - inneighbors
void unitTest7() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	
	int result = graph_add_edge(graph, 1, 2);
	int result2 = graph_add_edge(graph, 2, 3);
	int result3 = graph_add_edge(graph, 1, 3);

	int remove = graph_remove_node(graph, 2);	

	printf("total inNodes1, expected = %d, actual = %d\n", 0, getNumInNeighbors(graph, 1));
	//printf("total inNodes2, expected = %d, actual = %d\n", 1, getNumInNeighbors(graph, 2));
	printf("total inNodes3, expected = %d, actual = %d\n", 1, getNumInNeighbors(graph, 3));

	printInNeighbors(graph, 1);
	//printInNeighbors(graph, 2);
	printInNeighbors(graph, 3);	

	
	printf(".....\n");
	printf("...... test outneighbors\n");

	printf("total outNodes1, expected = %d, actual = %d\n", 1, getNumOutNeighbors(graph, 1));
	//printf("total outNodes2, expected = %d, actual = %d\n", 1, getNumOutNeighbors(graph, 2));
	printf("total outNodes3, expected = %d, actual = %d\n", 0, getNumOutNeighbors(graph, 3));

	printOutNeighbors(graph, 1);
	//printOutNeighbors(graph, 2);
	printOutNeighbors(graph, 3);	

	//printf("total nodes after remove, expected: %d, actual: %d\n", 1, remove);
	printf("total nodes after remove, expected: %d, actual: %d\n", 2, graph_num_nodes(graph));

	printf("......\n");
	printf("....print nodes.\n");

	printNodes(graph);

	free_graph(graph);
}
 

//unitTest8 
//test remove node
void unitTest8() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);
	
	int result = graph_add_edge(graph, 1, 2);
	int result2 = graph_add_edge(graph, 2, 3);
	int result3 = graph_add_edge(graph, 1, 3);
	int result4 = graph_add_edge(graph, 4, 2);


	printf("total nodes, expected = %d, actual = %d\n", 1, result);
	graph_node_t* findOne = find_node(graph, 1);
	graph_node_t* findTwo = find_node(graph, 2);

	printf("total nodes, expected = %d, actual = %d\n", 2, findOne -> outNeighbors -> count);	
	graph_remove_edge(graph, 1, 2);	
	printf("total nodes, expected = %d, actual = %d\n", 1, findOne -> outNeighbors -> count);
	printf("total nodes, expected = %d, actual = %d\n", 1, findTwo -> inNeighbors -> count);
	printOutNeighbors(graph, 1);
	printInNeighbors(graph, 2);

	free_graph(graph);
}


//unitTest9 
//test remove node
void unitTest9() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	
	printf("Nodes before remove\n\n");
	printNodes(graph);
	dll_remove(graph -> nodes, 0);
	printf("Nodes afrer remove\n\n");

	printNodes(graph);	

	free_graph(graph);
}
 
 
//unitTest10 
//test remove node
void unitTest10() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

int result = graph_add_edge(graph, 1, 2);
	int result2 = graph_add_edge(graph, 2, 3);

	graph_node_t* findOne = find_node(graph, 1);
	graph_node_t* findTwo = find_node(graph, 2);
	
	printf("Count before remove: %d\n", findOne -> outNeighbors -> count);
	dll_remove(findOne -> outNeighbors, 0);
	
	printf("Count after remove: %d\n", findOne -> outNeighbors -> count);
	
	
	int value = printOutNeighbors(graph, 1);	
	printf("No nodes left in outneighbors test, %d\n", value);

	free_graph(graph);
}



//unitTest11 
//test contains edge
void unitTest11() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	
	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	
	int result = contains_edge(graph, 1, 2);
	printf("contains edge, expected: %d, actual: %d\n", 1, result);

	int result2 = contains_edge(graph, 2, 3);	
	printf("contains edge, expected: %d, actual: %d\n", 1, result2);	

	int result3 = contains_edge(graph, 1, 3);	
	printf("contains edge, expected: %d, actual: %d\n", 0, result3);

	int result4 = contains_edge(graph, 2, 4);	
	printf("contains edge, expected: %d, actual: %d\n", 0, result4);
	free_graph(graph);
	
	
}
 
 
//unitTest12 
//test remove node
void unitTest12() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	
	dll_t* result1 = getInNeighbors(graph, 2);
	dll_t* result2 = getInNeighbors(graph, 3);

	graph_node_t* item1 = dll_pop_front(result1);
	graph_node_t* item2 = dll_pop_front(result2);
	graph_node_t* item3 = dll_pop_front(result2);

	printf("inNeighbor1 = %d\n", item1 -> data);	
	printf("inNeighbor3 = %d\n", item2 -> data);
	printf("inNeighbor3 = %d\n", item3 -> data);

	free_graph(graph);

}


//unitTest13 
//test numInNeighbors
void unitTest13() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	
	printf("number inNodes in 1, expected: %d, actual: %d\n", 0, getNumInNeighbors(graph, 1));
	printf("number inNodes in 2, expected: %d, actual: %d\n", 1, getNumInNeighbors(graph, 2));
	printf("number inNodes in 3, expected: %d, actual: %d\n", 2, getNumInNeighbors(graph, 3));

	free_graph(graph);
}


//unitTest14 
//test remove node
void unitTest14() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	
	dll_t* result1 = getOutNeighbors(graph, 1);
	dll_t* result2 = getOutNeighbors(graph, 1);
	dll_t* result3 = getOutNeighbors(graph, 2);

	graph_node_t* item1 = dll_pop_front(result1);
	graph_node_t* item2 = dll_pop_front(result2);
	graph_node_t* item3 = dll_pop_front(result3);

	printf("outNeighbor1 = %d\n", item1 -> data);	
	printf("outNeighbor1 = %d\n", item2 -> data);
	printf("outNeighbor2 = %d\n", item3 -> data);

	free_graph(graph);

}


//unitTest15 
//test numOutNeighbors
void unitTest15() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	
	printf("number outNodes in 1, expected: %d, actual: %d\n", 2, getNumOutNeighbors(graph, 1));
	printf("number outNodes in 2, expected: %d, actual: %d\n", 1, getNumOutNeighbors(graph, 2));
	printf("number outNodes in 3, expected: %d, actual: %d\n", 0, getNumOutNeighbors(graph, 3));

	free_graph(graph);
}

//unitTest16 
//test numInNeighbors
void unitTest16() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	
	printf("number edges, expected: %d, actual: %d\n", 3, graph_num_edges(graph));

	free_graph(graph);
}

//unitTest17 
//test queue of isReachable
void unitTest17() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);


	int value = is_reachable(graph, 1, 3);
	int value2 = is_reachable(graph, 1, 2);
	int value3 = is_reachable(graph, 1, 4);
	printf("isReachable: %d\n", value); 
	printf("isReachable: %d\n", value2); 
	printf("isReachable: %d\n", value3);
	
	free_graph(graph);	
}



//unitTest18 
//test queue of isReachable
void unitTest18() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);


	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 2, 4);
	graph_add_edge(graph, 3, 5);
	graph_add_edge(graph, 5, 6);


	int value = is_reachable(graph, 1, 6);
	int value2 = is_reachable(graph, 1, 7);
	int value3 = is_reachable(graph, 3, 4);
	int value4 = is_reachable(graph, 1, 2);
	int value5 = is_reachable(graph, 1, 3);
	int value6 = is_reachable(graph, 3, 6);
	int value7 = is_reachable(graph, 3, 1);
	int value8 = is_reachable(graph, 3, 2);
	

	
	printf("isReachable, expected: %d, actual: %d\n", 1, value); 
	printf("isReachable, expected: %d, actual: %d\n", -1, value2); 
	printf("isReachable, expected: %d, actual: %d\n", 0, value3);
	printf("isReachable, expected: %d, actual: %d\n", 1, value4); 
	printf("isReachable, expected: %d, actual: %d\n", 1, value5); 
	printf("isReachable, expected: %d, actual: %d\n", 1, value6);
	printf("isReachable, expected: %d, actual: %d\n", 0, value7); 
	printf("isReachable, expected: %d, actual: %d\n", 0, value8);
	
	free_graph(graph);

}


//unitTest26
//test queue of isReachable
void unitTest26() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);


	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 2, 4);
	graph_add_edge(graph, 3, 5);
	graph_add_edge(graph, 5, 6);
	
	int value = is_reachable(graph, 1, 7);
	printf("isReachable, expected: %d, actual: %d\n", -1, value);


}


//unitTest19 
//test queue of has cycle with cycle
void unitTest19() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 2, 4);
	graph_add_edge(graph, 3, 5);
	graph_add_edge(graph, 5, 6);

	int result = has_cycle(graph);
	
	printf("has cycle, expected: %d, actual: %d\n", 1,result);

}


//unitTest20 
//test queue of has cycle with cycle
void unitTest20() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	
	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);

	int result = has_cycle(graph);
	
	printf("has cycle, expected: %d, actual: %d\n", 0, result);

}



//unitTest21 
//test queue of has cycle with cycle
void unitTest21() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);	

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 4);
	graph_add_edge(graph, 4, 3);
	

	int result = has_cycle(graph);
	
	printf("has cycle, expcted: %d, actual: %d\n", 0, result);

}


//unitTest22 
//test queue of has cycle with cycle
void unitTest22() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);	

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 1, 4);
	graph_add_edge(graph, 3, 4);
	

	int result = has_cycle(graph);
	
	printf("has cycle, expcted: %d, actual: %d\n", 1, result);

}


//unitTest23 
//test queue of has cycle with cycle
void unitTest23() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);	
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);	

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 4);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 3, 6);
	graph_add_edge(graph, 6, 5);

	printf("....\n");
	printf("expected: 1-3-6-5\n");
	print_path(graph, 1, 5);	
	printf("....\n");
	printf("....\n");
	printf("expected: 1-3-6-5 -2-4\n");
	print_path(graph, 1, 4);
	printf("....\n");
	printf("....\n");
	printf("expected: 3-6-5\n");
	print_path(graph, 3, 5);
	printf("....\n");
	printf("....\n");
	printf("expected: path does not exist.\n");
	print_path(graph, 3, 7);	
	
}


//unitTest24 
//test queue of has cycle with cycle
void unitTest24() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);	
	graph_add_node(graph, 5);
	graph_add_node(graph, 6);	

	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 2, 3);
	graph_add_edge(graph, 2, 4);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 3, 6);
	graph_add_edge(graph, 6, 5);

	printf("....\n");
	printf("expected: 1-3-6-5\n");
	print_path(graph, 1, 5);	
	printf("....\n");
	printf("....\n");
	
}


//unitTest25 
//test queue of has cycle with cycle
void unitTest25() {
	
	graph_t* graph = create_graph();

	graph_add_node(graph, 1);
	graph_add_node(graph, 2);
	graph_add_node(graph, 3);
	graph_add_node(graph, 4);	
	
	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 1, 3);
	graph_add_edge(graph, 3, 2);
	graph_add_edge(graph, 4, 3);
	graph_add_edge(graph, 5, 2);

	printf("....\n");
	printf("expected: path does not exit.\n");
	print_path(graph, 1, 4);	
	printf("....\n");
	printf("....\n");
	
}
 

 

int main(int argc, const char * argv[]) {

	printf("\n New Test 1....................\n"); 
	unitTest1(); 
	
	printf("\n New Test 2....................\n"); 
	unitTest2(); 

	printf("\n New Test 3....................\n"); 
	unitTest3(); 
	
	printf("\n New Test 4....................\n"); 
	unitTest4(); 

	
	printf("\n New Test 5....................\n"); 
	unitTest5(); 

	printf("\n New Test 6....................\n"); 
	unitTest6(); 
	
	printf("\n New Test 7....................\n"); 
	unitTest7(); 
		
	printf("\n New Test 8....................\n"); 
	unitTest8(); 
			
	printf("\n New Test 9....................\n"); 
	unitTest9(); 

	printf("\n New Test 10....................\n"); 
	unitTest10(); 
	
	printf("\n New Test 11....................\n"); 
	unitTest11();
	
 	printf("\n New Test 12....................\n"); 
	unitTest12(); 

	printf("\n New Test 13....................\n"); 
	unitTest13(); 
	
	printf("\n New Test 14....................\n"); 
	unitTest14();
	
	printf("\n New Test 15....................\n"); 
	unitTest15(); 
	 
	printf("\n New Test 16....................\n"); 
	unitTest16(); 

	printf("\n New Test 17....................\n"); 
	unitTest17();
			
	printf("\n New Test 18....................\n"); 
	unitTest18();

	printf("\n New Test 19....................\n"); 
	unitTest19();
	
	printf("\n New Test 20....................\n"); 
	unitTest20();	
		
	printf("\n New Test 21....................\n"); 
	unitTest21();	

	printf("\n New Test 22....................\n"); 
	unitTest22();	
	
	printf("\n New Test 23....................\n"); 
	unitTest23();	
		
	printf("\n New Test 24....................\n"); 
	unitTest24();	
	
	printf("\n New Test 25....................\n"); 
	unitTest25();	

	printf("\n New Test 26....................\n"); 
	unitTest26();	
			
}
