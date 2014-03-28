#ifndef HEAP_H
#define HEAP_H

#include "helpers.h"

class Heap
{
	int heapMaxSize;
	int heapCurrentSize;
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
	void  maxHeapify(int i);
	void  buildMaxHeap();

	/* Heap Operations */
	heapNode getMaximum();
	void  insertElement(heapNode hNode);
	void  deleteRoot();
	void  deleteElement(int key);
	void  heapSort();

	/* Misc Helper Functions */
	void  printHeapArray();
	int   getHeapCurrentSize();
	float showHeapElement(int key);
	heapNode* getHeapArray();
	static void  heapTest();
};

#endif /* HEAP_H */