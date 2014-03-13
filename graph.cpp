#include "graph.h"

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

void Graph::makeVertexSets()
{
	for (int i = 1; i <= numberOfVertices; i++)
	{
		adjListNode *listNode = adjacencyList[i-1];
		if(listNode)
		{
			listNode->nodeVal = i;
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

void Graph::addEdge(int u, int v)
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

	adjListNode *listNode = adjacencyList[u-1];
	adjListNode *tempNode = listNode;
	while(tempNode->next != NULL)
	{
		tempNode = tempNode->next;
	}
	adjListNode *newNode = new adjListNode;
	newNode->nodeVal = v;
	newNode->next    = NULL;
	tempNode->next   = newNode;
}

Graph::~Graph()
{
	for(int i = 0; i < this->numberOfVertices; i++)
	{
		delete adjacencyList[i];
	}
}

int main()
{
	Graph *g = new Graph(10);
	g->makeVertexSets();
	g->addEdge(1,2);
	g->printGraph();
	delete g;
	char a = getchar();
	return 1;
}