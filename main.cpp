#include <iostream>
#include "graph.h"
#include "heap.h"

using namespace std;

int main()
{
	/* Graph Testing
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2,50);
	g->addEdge(1,3,20);
	g->addEdge(4,5,10);
	g->addEdge(1,4,5);
	g->printGraph();
	delete g;
	*/

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