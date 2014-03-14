#include "heap.h"
#include <math.h>
#include <iostream>

using namespace std;

Heap::Heap(int size)
{
	this->heapMaxSize	  = size;
	this->heapCurrentSize = 0;
	heapArray = new float[size];
}

Heap::~Heap()
{
	delete [] heapArray;
}

int Heap::getParent(int i)
{
	if (i == 0)
	{
		return -1;
	}
	else
	{
		return (ceil(float(i/2)) - 1);
	}
}

int Heap::getLeft(int i)
{
	return (2*i + 1);
}

int Heap::getRight(int i)
{
	return (2*i + 2);
}

void Heap::minHeapify(int i)
{
	int smallest;
	int left  = getLeft (i);
	int right = getRight(i);

	if ((left < this->heapCurrentSize) && (heapArray[left] < heapArray[i]))
	{
		smallest = left;
	}
	else
	{
		smallest = i;
	}

	if ((right < this->heapCurrentSize) && (heapArray[right] < heapArray[smallest]))
	{
		smallest = right;
	}

	if (smallest != i)
	{
		/* Swap heapArray[i] and heapArray[smallest] */
		float temp = heapArray[i];
		heapArray[i]		= heapArray[smallest];
		heapArray[smallest] = temp;

		minHeapify(smallest);
	}
}

void Heap::buildMinHeap()
{
	int heapCurrSize = heapCurrentSize;
	int heapMid = ceil(float(heapCurrSize/2)) - 1;
	for (int i = heapMid; i >=0; i--)
	{
		minHeapify(i);
	}
}

float Heap::getMinimum()
{
	return heapArray[0];
}

void Heap::insertElement(float value)
{
	heapCurrentSize += 1;
	heapArray[heapCurrentSize - 1] = value;

	int index = heapCurrentSize - 1;
	while( (index > 0) && (heapArray[getParent(index)] > heapArray[index]))
	{
		float temp					=	 heapArray[getParent(index)];
		heapArray[getParent(index)]	=	 heapArray[index];
		heapArray[index]            =	 temp;

		index						=	 getParent(index);
	}
}

void Heap::deleteRoot()
{
	heapArray[0]	 = heapArray[heapCurrentSize - 1];
	heapCurrentSize -= 1;
	minHeapify(0);
}

void Heap::printHeapArray()
{
	cout << "Printing heap elements!" << endl;
	for (int i = 0; i < heapCurrentSize; i++)
	{
		cout << heapArray[i] << '\t';
	}
	cout << endl;
}

int Heap::getHeapCurrentSize()
{
	return heapCurrentSize;
}