#include <iostream>
#include <cstdlib>
#include <ctime>
#include "graph.h"

using namespace std;

Graph::Graph(int numVertices)
{
	this->numberOfVertices = numVertices;
	this->numberOfEdges    = 0;

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

int Graph::getNumberOfEdges()
{
	return this->numberOfEdges;
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
	return 0;
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
	this->numberOfEdges++;
}

bool Graph::doesEdgeExist(int v1, int v2)
{
	adjListNode* neighborListV1 = adjacencyList[v1 - 1];
	adjListNode* temp = neighborListV1->next;
	while(temp != NULL)
	{
		if ((temp != NULL))
		{
			if (temp->nodeVal == v2)
				return true;
		}
		temp = temp->next;
	}
	return false;
}

Graph* Graph::generateRandomGraph(int numberOfVertices, int nodeDegree)
{
	Graph *g = new Graph(numberOfVertices);
	g->makeVertexSets();
	adjListNode **adjacencyList = g->getAdjacencyList();
	srand(time(0));
	for (int i = 1; i <= numberOfVertices; i++)
	{
		int attempts = 0;
		adjListNode *vertex  = adjacencyList[i-1];
		int randomVertex;
		int randomEdgeWeight;
		while (vertex->nodeDegree < nodeDegree)
		{
			randomVertex		= rand() % (numberOfVertices * 2) + 1;
			randomEdgeWeight	= rand() % (numberOfVertices * 2) + 1;
			if (!g->doesEdgeExist(i, randomVertex) && (randomVertex != i) && (adjacencyList[randomVertex-1]->nodeDegree < nodeDegree))
			{
				g->addEdge(i, randomVertex, randomEdgeWeight);
			}
			attempts++;
			if (attempts > 20000)
			{
				delete g;
				return 0;
			}
			
		}
		
	}
	return g;
}

Graph* Graph::generateRandomGraph(int numberOfVertices, float outgoingEdgeRatio)
{
	Graph *g = new Graph(numberOfVertices);
	g->makeVertexSets();
	adjListNode **adjacencyList = g->getAdjacencyList();
	srand(time(0));
	for (int i = 1; i <= numberOfVertices; i++)
	{
		adjListNode *vertex  = adjacencyList[i-1];
		for (int j = 1; j <= outgoingEdgeRatio * numberOfVertices; j++)
		{
			int randomEdgeWeight;
			int randomVertexNumber;
			randomVertexNumber	= rand() % (numberOfVertices * 2) + 1;
			randomEdgeWeight	= rand() % (numberOfVertices * 2) + 1;
			if (!g->doesEdgeExist(i, randomVertexNumber) && (randomVertexNumber != i) && 
				(vertex->nodeDegree < (outgoingEdgeRatio * numberOfVertices)) && (adjacencyList[randomVertexNumber-1]->nodeDegree < ((outgoingEdgeRatio * numberOfVertices))))
			{
				g->addEdge(i, randomVertexNumber, randomEdgeWeight);
			}

		}
		
	}
	return g;
}

void Graph::printVertexDegree()
{
	for (int i = 1; i <= numberOfVertices; i++)
	{
		adjListNode *listNode = adjacencyList[i-1];
		if (listNode != NULL)
		{
			cout << listNode->nodeVal << ": " << listNode->nodeDegree << endl;
		}
	}	
}

void Graph::graphTest()
{
	// Creating graph
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2,50);
	g->addEdge(1,3,20);
	g->addEdge(4,5,10);
	g->addEdge(1,4,5);
	g->addEdge(3,5,10);
	g->addEdge(2,3,5);
	
	/*
	int *pathV = new int[10];
	breadthFirstSearch(g, 1, 8, pathV);
	for (int i = 0; i < 10; i++)
	{
		cout << pathV[i];
	}
	char t = getchar();
	*/
	return; 
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
