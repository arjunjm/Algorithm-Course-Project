#include <iostream>
#include "graph.h"
#include "heap.h"
#include "maxBWpath.h"

using namespace std;

int main()
{
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2,50);
	g->addEdge(1,3,20);
	g->addEdge(4,5,10);
	g->addEdge(1,4,5);
	g->addEdge(3,5,10);
	//g->printGraph();

	int		vertexCount		 = g->getNumberOfVertices();
	int		*pVector		 = new int[vertexCount];
	float   *bandwidthVector = new float[vertexCount];

	runMaxBWPathDijkstraNoHeap(g, 4, 3, pVector, bandwidthVector);

	for (int i = 0; i < g->getNumberOfVertices(); i++)
		cout << pVector[i] << '\t';
	cout <<endl;

	for (int i = 0; i < g->getNumberOfVertices(); i++)
		cout << bandwidthVector[i] << '\t';
	cout << endl;

	delete g;
	

	/* Heap Test
	Heap *heap = new Heap(10);
	heap->insertElement(23.5);
	heap->insertElement(10);
	heap->insertElement(2.5);
	heap->insertElement(1.8);
	heap->insertElement(3);
	heap->insertElement(8);
	heap->buildMinHeap();
	heap->printHeapArray();

	float minimum;
	while ( heap->getHeapCurrentSize() )
	{
		minimum = heap->getMinimum();
		heap->deleteRoot();
		cout << minimum << '\t';
	}
	cout << endl;
	delete heap;
	*/

	char a = getchar();
	return 1;
}