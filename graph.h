#ifndef GRAPH_H
#define GRAPH_H

#include "helpers.h"

class Graph
{
	int numberOfVertices;
	adjListNode **adjacencyList;

public:
	Graph(int numVertices);
	int  getNumberOfVertices();
	adjListNode** getAdjacencyList();
	void makeVertexSets();
	void printGraph();
	void addEdge(int u, int v, float edgeWeight);
	~Graph();
};

#endif /* GRAPH_H */
