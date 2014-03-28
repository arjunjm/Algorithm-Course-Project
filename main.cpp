#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include "graph.h"
#include "heap.h"
#include "maxBWpath.h"

using namespace std;

int main()
{
	// Creating graph
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2,50);
	g->addEdge(1,3,20);
	g->addEdge(4,5,10);
	g->addEdge(1,4,5);
	g->addEdge(3,5,10);
	g->addEdge(2,3,5);
	//g->printGraph();

	int		vertexCount		 = g->getNumberOfVertices();
	int sourceVertex = 2;
	int destVertex = 4;

	// Algorithm #1
	cout << "Calculating Maximum Bandwidth Path Using Dijkstra's Method without heap" << endl;
	cout << "=======================================================================" << endl;

	int		*pVector_1		   = new int[vertexCount];
	float   *bandwidthVector_1 = new float[vertexCount];
	
	runMaxBWPathDijkstraNoHeap(g, sourceVertex, destVertex, pVector_1, bandwidthVector_1);

	// The stack is just used for ease in printing the path
	stack<int> vertexStack_1;

	vertexStack_1.push(destVertex);
	int vertex = pVector_1[destVertex - 1];
	do
	{
		vertexStack_1.push(vertex);
		if (vertex == sourceVertex)
			break;
		vertex = pVector_1[vertex - 1];
	} while (true);

	cout << "Max Bandwidth Path  :: ";
	while(!vertexStack_1.empty())
	{
		cout << vertexStack_1.top();
		if (vertexStack_1.top() != destVertex)
			cout << "-->";
		vertexStack_1.pop();
	}

	cout << endl;
	cout << "Max Bandwidth Value :: " << bandwidthVector_1[destVertex - 1] << endl;

	cout << "---------------------------------------------------------------------------";
	cout << endl << endl << endl;

	delete pVector_1;
	delete bandwidthVector_1;

	// Algorithm #2
	cout << "Calculating Maximum Bandwidth Path Using Dijkstra's Method with heap" << endl;
	cout << "====================================================================" << endl;

	int		*pVector_2		   = new int[vertexCount];
	float   *bandwidthVector_2 = new float[vertexCount];
	
	runMaxBWPathDijkstraWithHeap(g, sourceVertex, destVertex, pVector_2, bandwidthVector_2);
	
	// The stack is just used for ease in printing the path
	stack<int> vertexStack_2;

	vertexStack_2.push(destVertex);
	int vertexVal = pVector_2[destVertex - 1];
	do
	{
		vertexStack_2.push(vertexVal);
		if (vertexVal == sourceVertex)
			break;
		vertexVal = pVector_2[vertexVal - 1];
	} while (true);

	cout << "Max Bandwidth Path  :: ";
	while(!vertexStack_2.empty())
	{
		cout << vertexStack_2.top();
		if (vertexStack_2.top() != destVertex)
			cout << "-->";
		vertexStack_2.pop();
	}

	cout << endl;
	cout << "Max Bandwidth Value :: " << bandwidthVector_2[destVertex - 1] << endl;

	cout << "---------------------------------------------------------------------------";
	cout << endl << endl << endl;

	delete pVector_2;
	delete bandwidthVector_2;

	// Algorithm #3
	cout << "Calculating Maximum Bandwidth Path Using Kruskal's Method" << endl;
	cout << "=========================================================" << endl;
	int *pVector_3			   = new int[vertexCount];
	runMaxBWPathKruskal(g, sourceVertex, destVertex, pVector_3);

	stack<int> vertexStack_3;
	int predecessorVertex = pVector_3[destVertex - 1];
	vertexStack_3.push(destVertex);
	
	int bandwidth = g->getEdgeWeight(destVertex, predecessorVertex);
	int temp = 0;
	do
	{
		vertexStack_3.push(predecessorVertex);
		if (predecessorVertex == sourceVertex)
			break;
		temp = g->getEdgeWeight(predecessorVertex, pVector_3[predecessorVertex - 1]);
		if (temp < bandwidth)
			bandwidth = temp;
		predecessorVertex = pVector_3[predecessorVertex - 1];	
	}while (true);

	cout << "Max Bandwidth Path  :: ";
	while(!vertexStack_3.empty())
	{
		cout << vertexStack_3.top();
		if (vertexStack_3.top() != destVertex)
			cout << "-->";
		vertexStack_3.pop();
	}

	cout << endl;
	cout << "Max Bandwidth Value :: " << bandwidth << endl;
	cout << "---------------------------------------------------------------------------";

	cout << endl << endl << endl;
	
	delete g;
	
	char a = getchar();
	return 1;
}