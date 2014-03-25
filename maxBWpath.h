#ifndef MAX_PATH_H
#define MAX_PATH_H

#include "graph.h"
#include "heap.h"

enum NodeStatus
{
	NODE_UNSEEN,
	NODE_FRINGE,
	NODE_INTREE
};

/* This enum will be used to track the node color during BFS */
enum NodeColor
{
	WHITE,  /* Node not yet processed */
	GRAY,  /* Node processing ongoing */
	BLACK /* Node processing complete */
};

/* Helper functions*/
int findSet(int vertexNumber, int* parentVector);
void doUnion(int r1, int r2, int* rankVector, int* parentVector);
void makeSet(int vertexNumber, int* parentVector);
void breadthFirstSearch(Graph *g, int sourceVertex, int destVertex, int *pathvVector);

void runMaxBWPathDijkstraNoHeap(Graph *g, int sourceVertex, int destVertex, int* parentVector, float* bandwidthVector);
void runMaxBWPathDijkstraWithHeap(Graph *g, int sourceVertex, int destVertex, int* parentVector, float* bandwidthVector);
void runMaxBWPathKruskal(Graph *g, int sourceVertex, int destVertex, int* pathVector);

#endif /* MAX_PATH_H */