#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "heap.h"
#include "maxBWpath.h"

using namespace std;

int main()
{
	// Graph-heap testing
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2,50);
	g->addEdge(1,3,20);
	g->addEdge(4,5,10);
	g->addEdge(1,4,5);
	g->addEdge(3,5,2);
	g->addEdge(2,3,5);
	//g->printGraph();

	int		vertexCount		 = g->getNumberOfVertices();
	int		*pVector		 = new int[vertexCount];
	float   *bandwidthVector = new float[vertexCount];

	//runMaxBWPathDijkstraWithHeap(g, 2, 5, pVector, bandwidthVector);
	runMaxBWPathKruskal(g, 1, 5, pVector, bandwidthVector);
	
#if 0
	for (int i = 0; i < g->getNumberOfVertices(); i++)
		cout << pVector[i] << '\t';
	cout <<endl;

	for (int i = 0; i < g->getNumberOfVertices(); i++)
		cout << bandwidthVector[i] << '\t';
	cout << endl;
#endif

	delete g;
	

	/* Heap Test
	heapNode hNode;
	Heap *heap = new Heap(1000);
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		hNode.key	= i;
		hNode.value	= rand() % 1000;
		heap->insertElement(hNode);
	}
	hNode.key = 50;
	hNode.value = 1000;
	heap->insertElement(hNode);
	//heap->buildMaxHeap();
	heap->printHeapArray();

	heapNode maximum;

	int key = 13;
	cout << "Generated key = " << key << endl;
	cout << "Deleting element " << heap->showHeapElement(key) << endl;
	heap->deleteElement(key);
	

	while ( heap->getHeapCurrentSize() )
	{
		maximum = heap->getMaximum();
		heap->deleteRoot();
		cout << maximum.value << '\t';
	}
	cout << endl;
	delete heap;
	*/

	char a = getchar();
	return 1;
}