#ifndef GRAPH_H
#define GRAPH_H

#include "helpers.h"

class Graph
{
	int numberOfVertices;
	int numberOfEdges;
	adjListNode **adjacencyList;

public:
	Graph(int numVertices);
	int  getNumberOfVertices();
	int  getNumberOfEdges();
	adjListNode** getAdjacencyList();
	void makeVertexSets();
	void printGraph();
	void addEdge(int u, int v, float edgeWeight);
	~Graph();

	/* Helper functions */
	float getEdgeWeight(int v1, int v2);
	bool  doesEdgeExist(int v1, int v2);
	void  printVertexDegree();
	void  graphTest();
    void  addCycle();

	/* Random Graph generation functions */
	static Graph* generateRandomGraph(int numVertices, int nodeDegree);
	static Graph* generateRandomGraph(int numVertices, float outgoingEdgeRatio);
};

#endif /* GRAPH_H */
