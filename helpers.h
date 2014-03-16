#ifndef HELPERS_H
#define HELPERS_H

#include <limits.h>

#define NULL 0

struct adjListNode
{
	int nodeVal;
	int nodeDegree;
	float edgeWeight;
	adjListNode* next;
};

void addToListEnd(adjListNode* listHead, int nodeValue, float edgeWeight);
float getMinimum(float a, float b);

#endif /* HELPERS_H */