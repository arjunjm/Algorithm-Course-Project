#include "helpers.h"

class Graph
{
	int numberOfVertices;
	adjListNode **adjacencyList;

public:
	Graph(int numVertices);
	void makeVertexSets();
	void printGraph();
	void addEdge(int u, int v, float edgeWeight);
	~Graph();
};


