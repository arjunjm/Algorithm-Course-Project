#ifndef HEAP_H
#define HEAP_H

#include "helpers.h"

class Heap
{
	int heapMaxSize;
	int heapCurrentSize;
	//float *heapArray;
	heapNode *heapArray;

public:

	/* Heap Constructor */
	Heap(int size);

	/* Heap Destructor */
	~Heap();

	/* Heap Index Functions */
	int getParent(int i);
	int getLeft(int i);
	int getRight(int i);

	/* Heap Building Functions */
	void  minHeapify(int i);
	void  buildMinHeap();

	/* Heap Operations */
	float getMinimum();
	void  insertElement(heapNode hNode);
	void  deleteRoot();

	/* Misc Helper Functions */
	void  printHeapArray();
	int   getHeapCurrentSize();
};

#endif /* HEAP_H */