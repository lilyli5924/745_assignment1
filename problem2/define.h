#ifndef _DEFINE_H
#define _DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int vertex;
    int weight;
    Node* next;
};

struct LList {
    struct Node* head;
};

struct Edge {
    int src;
    int dest;
    int weight;
};

struct Index {
    int success;
    int index;
};

// create a size V array, where each array initially has only a node head
struct Graph {
    int V;		 	// size of the array
    struct LList* llist;	// graph is an array of AdjList
};

struct minVertex {
    int vertex;
    int distance;
};

struct VertexSet {
    int current_size;   // currently how many nodes present in this set
    int size;           // total size of the set
    struct minVertex** list;  // pointer(addr) --> pointer(address) --> variable(value)
};

struct Graph* printGraph(const char*);
struct Graph* createGraph(const char*);
struct Node* newAdjNode(int, int);

struct minVertex* newMinVertex(int, int);
struct VertexSet* createVertexSet(int);
int isEmpty(struct VertexSet*);
struct Index isInVertexSet(struct VertexSet*, int);
struct minVertex* extract(struct VertexSet*);
struct minVertex* extract_minimum(struct VertexSet*, int*);
void printSPath(int[], int, int);
void dijkstra_shortest_path(struct Graph*, int, int);
void dijkstra_shortest_path_heap(struct Graph*, int, int);
void heapifyDown(struct VertexSet*, int, int*);
int isIn_heap(int*, int);
void decreaseDist(struct VertexSet*, int*, int, int);

#endif
