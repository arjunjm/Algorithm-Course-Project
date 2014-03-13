#include <iostream>

using namespace std;

struct adjListNode
{
	int nodeVal;
	adjListNode* next;
};

class Graph
{
	int numberOfVertices;
	adjListNode **adjacencyList;

public:
	Graph(int numVertices);
	void makeVertexSets();
	void printGraph();
	void addEdge(int u, int v);
	~Graph();
};


