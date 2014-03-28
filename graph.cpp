#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph(int numVertices)
{
	this->numberOfVertices = numVertices;

	// Creates an array of pointers.
	adjacencyList          = new adjListNode*[this->numberOfVertices];
	for (int i = 0; i < this->numberOfVertices; i++)
	{
		adjacencyList[i] = new adjListNode;
	}
}

int Graph::getNumberOfVertices()
{
	return this->numberOfVertices;
}

float Graph::getEdgeWeight(int v1, int v2)
{
	adjListNode* neighborListV1 = adjacencyList[v1 - 1];
	adjListNode* temp = neighborListV1->next;
	while(temp != NULL)
	{
		if (temp->nodeVal == v2)
		{
			return temp->edgeWeight;
		}
		temp = temp->next;
	}
}

adjListNode** Graph::getAdjacencyList()
{
	return adjacencyList;
}

void Graph::makeVertexSets()
{
	for (int i = 1; i <= numberOfVertices; i++)
	{
		adjListNode *listNode = adjacencyList[i-1];
		if(listNode)
		{
			listNode->nodeVal = i;
			listNode->nodeDegree = 0;
			listNode->edgeWeight = 0;
			listNode->next    = NULL;
		}
		else
		{
			cout << "listNode is NULL!";
		}
	}
}

void Graph::printGraph()
{
	for (int i = 1; i <= numberOfVertices; i++)
	{
		adjListNode *listNode = adjacencyList[i-1];
		adjListNode *tempNode = listNode;
		while(tempNode != NULL)
		{
			cout << tempNode->nodeVal << "-->";
			tempNode = tempNode->next;
		}
		cout << "NULL";
		cout << endl;
	}
}

void Graph::addEdge(int u, int v, float edgeWeight)
{
	if (u < 0 || u > this->numberOfVertices)
	{	
		cout << "Vertex " << u << " does not exist";
		return;
	}

	if (v < 0 || v > this->numberOfVertices)
	{	
		cout << "Vertex " << v << " does not exist";
		return;
	}

	adjListNode *listHeadFirstVertex  = adjacencyList[u-1];
	adjListNode *listHeadSecondVertex = adjacencyList[v-1];
	addToListEnd(listHeadFirstVertex, v, edgeWeight);
	addToListEnd(listHeadSecondVertex, u, edgeWeight);
	listHeadFirstVertex->nodeDegree++;
	listHeadSecondVertex->nodeDegree++;
}

Graph::~Graph()
{
	for(int i = 0; i < this->numberOfVertices; i++)
	{
		adjListNode* listHead = adjacencyList[i];
		adjListNode* tempNode = listHead;
		while(tempNode)
		{
			adjListNode* oldNode = tempNode;
			tempNode = tempNode->next;
			delete oldNode;
		}
	}
}
