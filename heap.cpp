#include "heap.h"
#include <math.h>
#include <iostream>

using namespace std;

Heap::Heap(int size)
{
	this->heapMaxSize	  = size;
	this->heapCurrentSize = 0;
	heapArray = new heapNode[size];
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
		return (ceil(float(i)/2) - 1);
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

void Heap::maxHeapify(int i)
{
	int largest;
	int left  = getLeft (i);
	int right = getRight(i);

	if ((left < this->heapCurrentSize) && (heapArray[left].value >= heapArray[i].value))
	{
		largest = left;
	}
	else
	{
		largest = i;
	}

	if ((right < this->heapCurrentSize) && (heapArray[right].value > heapArray[largest].value))
	{
		largest = right;
	}

	if (largest != i)
	{
		/* Swap heapArray[i] and heapArray[smallest] */
		float temp				  = heapArray[i].value;
		heapArray[i].value		  = heapArray[largest].value;
		heapArray[largest].value = temp;

		maxHeapify(largest);
	}
}

void Heap::buildMaxHeap()
{
	int heapCurrSize = heapCurrentSize;
	int heapMid = ceil(float(heapCurrSize/2)) - 1;
	for (int i = heapMid; i >=0; i--)
	{
		maxHeapify(i);
	}
}

heapNode Heap::getMaximum()
{
	if (this->heapCurrentSize > 0)
	{
		return heapArray[0];
	}
}

void Heap::insertElement(heapNode hNode)
{
	heapCurrentSize += 1;
	heapArray[heapCurrentSize - 1] = hNode;
	int index = heapCurrentSize - 1;
	while( (index > 0) && (heapArray[getParent(index)].value < heapArray[index].value))
	{
		float temp							=	 heapArray[getParent(index)].value;
		heapArray[getParent(index)].value	=	 heapArray[index].value;
		heapArray[index].value              =	 temp;
		index								=	 getParent(index);
	}
}

void Heap::deleteRoot()
{
	heapArray[0]	 = heapArray[heapCurrentSize - 1];
	heapCurrentSize -= 1;
	maxHeapify(0);
}

void Heap::deleteElement(int key)
{
	int elementIndex = -1;

	for (int i = 0; i < this->heapCurrentSize; i++)
	{
		if (heapArray[i].key == key)
		{
			elementIndex = i;
		}
	}

	if(elementIndex == -1)
	{
		cout << "Element with key " << key << " not found in heap \n";
		return;
	}

	heapArray[elementIndex] = heapArray[heapCurrentSize - 1];
	heapCurrentSize -= 1;
	/* Sift the new element up or down depending on its value */
	if ((elementIndex != 0) && (heapArray[elementIndex].value > heapArray[getParent(elementIndex)].value))
	{
		while((elementIndex > 0) && (heapArray[elementIndex].value > heapArray[getParent(elementIndex)].value))
		{
			float temp									=	 heapArray[getParent(elementIndex)].value;
			heapArray[getParent(elementIndex)].value	=	 heapArray[elementIndex].value;
			heapArray[elementIndex].value               =	 temp;
			elementIndex								=	 getParent(elementIndex);
		}
	}
	else
	{
		maxHeapify(elementIndex);
	}
}

void Heap::printHeapArray()
{
	for (int i = 0; i < heapCurrentSize; i++)
	{
		cout << heapArray[i].value << '\t';
	}
	cout << endl;
}

int Heap::getHeapCurrentSize()
{
	return heapCurrentSize;
}

float Heap::showHeapElement(int key)
{
	return heapArray[key].value;
}