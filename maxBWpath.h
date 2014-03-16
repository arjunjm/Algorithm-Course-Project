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

void runMaxBWPathDijkstraNoHeap(Graph *g, int sourceVertex, int destVertex, int* parentVector, float* bandwidthVector);
void runMaxBWPathDijkstraWithHeap(Graph g, int sourceVertex, int destVertex);
void runMaxBWPathKruskal(Graph g, int sourceVertex, int destVertex);

#endif /* MAX_PATH_H */