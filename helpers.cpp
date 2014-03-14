#include "helpers.h"

void addToListEnd(adjListNode* listHead, int nodeValue, float edgeWeight)
{
	adjListNode *tempNode = listHead;
	while(tempNode->next != NULL)
	{
		tempNode = tempNode->next;
	}
	adjListNode *newNode = new adjListNode;
	newNode->nodeVal    = nodeValue;
	newNode->edgeWeight = edgeWeight;
	newNode->next    = NULL;
	tempNode->next   = newNode;
}