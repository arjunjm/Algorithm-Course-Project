#include "maxBWpath.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include <queue>
#include <time.h>

using namespace std;

/* Helper functions */
struct pairHasher
{
	size_t operator()(const pair<int, int> &p) const
	{
		return (hash<int>()(p.first) ^ hash<int>()(p.second));
	}
};

pair<int, int> swapPairContent(pair<int, int> p)
{
	pair<int, int> swappedPair;
	swappedPair.first  = p.second;
	swappedPair.second = p.first;
	return swappedPair;
}

void makeSet(int vertexNumber, int *parentVector, int *rankVector)
{
	parentVector[vertexNumber - 1] = vertexNumber;
	rankVector[vertexNumber - 1] = 0;
}

int findSet(int vertexNumber, int *parentVector)
{
	if (parentVector[vertexNumber - 1] != vertexNumber)
		return findSet(parentVector[vertexNumber - 1], parentVector);
	return parentVector[vertexNumber - 1];
}

void doUnion(int v1, int v2, int *rankVector, int *parentVector)
{
	if (rankVector[v1 - 1] < rankVector[v2 - 1])
	{
		parentVector[v1 - 1] = v2;
	}
	else if (rankVector[v1 - 1] > rankVector[v2 - 1])
	{
		parentVector[v2 - 1] = v1;
	}
	else
	// equal to case
	{
		parentVector[v1 - 1] = v2;
		rankVector[v2 - 1]   += 1;
	}
}

void breadthFirstSearch(Graph *g, int sourceVertex, int destVertex, int* pathVector)
{
	int vertexCount = g->getNumberOfVertices();
	adjListNode** adjacencyList = g->getAdjacencyList();
	NodeColor *colorVector = new NodeColor[vertexCount];
	queue <int> vertexQueue;

	for (int i = 0; i < vertexCount; i++)
	{
		colorVector[i] = WHITE;
		pathVector[i]  = 0;
	}

	colorVector[sourceVertex - 1] = GRAY;
	vertexQueue.push(sourceVertex);

	int temp;
	adjListNode* neighborList;
	while(!vertexQueue.empty())
	{
		temp = vertexQueue.front();
		vertexQueue.pop();
		neighborList = adjacencyList[temp - 1]->next;
		while(neighborList != NULL)
		{
			int vertexNumber = neighborList->nodeVal;
			if(colorVector[vertexNumber - 1] == WHITE)
			{
				colorVector[vertexNumber - 1] = GRAY;
				pathVector[vertexNumber - 1] = temp;
				vertexQueue.push(neighborList->nodeVal);
			}
			neighborList = neighborList->next;
		}
		colorVector[temp - 1] = BLACK; // Processing done!
	}
}

/* Max Bandwidth Algorithms */
void runMaxBWPathDijkstraNoHeap(Graph *g, int sourceVertex, int destVertex, int *parentVector, float *bandwidthVector)
{
	int vertexCount = g->getNumberOfVertices();
	NodeStatus *vertexStatus    = new NodeStatus[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		vertexStatus[i] = NODE_UNSEEN;
	}

	/* Initializing values for the source vertex */
	vertexStatus[sourceVertex - 1]		= NODE_INTREE;
	bandwidthVector[sourceVertex - 1]	= 0;

	adjListNode** adjacencyList		= g->getAdjacencyList();
	adjListNode* sourceNeighborList = adjacencyList[sourceVertex - 1]; 
	adjListNode* temp = sourceNeighborList->next;
	int neighborVertexNumber;
	float edgeWeight;
	while( temp != NULL)
	{
		neighborVertexNumber = temp->nodeVal;
		edgeWeight           = temp->edgeWeight;
		vertexStatus[neighborVertexNumber - 1]	  = NODE_FRINGE;
		bandwidthVector[neighborVertexNumber - 1] = edgeWeight;
		parentVector[neighborVertexNumber - 1]    = sourceVertex;
		temp = temp->next;
	}

	for (int i = 0; i < vertexCount; i++)
	{
		float maximum;
		int maximumFlowVertexIndex = 0, j = 0;
		while(j < vertexCount)
		{
			if (vertexStatus[j] == NODE_FRINGE)
			{
				maximumFlowVertexIndex = j;
				maximum = bandwidthVector[j];
				break;
			}
			j++;
		}
		for (int k = j + 1; k < vertexCount; k++)
		{
			if ((vertexStatus[k] == NODE_FRINGE) && (bandwidthVector[k] > maximum))
			{
				maximum = bandwidthVector[k];
				maximumFlowVertexIndex = k;
			}
		}
		vertexStatus[maximumFlowVertexIndex] = NODE_INTREE;
		adjListNode* neighborList = adjacencyList[maximumFlowVertexIndex]->next;
		adjListNode* tempNode     = neighborList;
		int neighborVertex, neighborEdgeWeight;
		while (tempNode != NULL)
		{
			neighborVertex		= tempNode->nodeVal;
			neighborEdgeWeight	= tempNode->edgeWeight;
			switch (vertexStatus[neighborVertex - 1])
			{
				case NODE_UNSEEN:
					vertexStatus[neighborVertex - 1]	= NODE_FRINGE;
					bandwidthVector[neighborVertex - 1] = getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight);
					parentVector[neighborVertex - 1]    = maximumFlowVertexIndex + 1;
					break;

				case NODE_FRINGE:
					if (bandwidthVector[neighborVertex - 1] < getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight))
					{
						bandwidthVector[neighborVertex - 1] = getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight);
						parentVector[neighborVertex - 1]    = maximumFlowVertexIndex + 1;
					}
					break;
			}
			tempNode = tempNode->next;
		}
	}
}

void runMaxBWPathDijkstraWithHeap(Graph *g, int sourceVertex, int destVertex, int* parentVector, float* bandwidthVector)
{
	int vertexCount = g->getNumberOfVertices();
	Heap *h	= new Heap(vertexCount);
	NodeStatus *vertexStatus    = new NodeStatus[vertexCount];
	for (int i = 0; i < vertexCount; i++)
	{
		vertexStatus[i] = NODE_UNSEEN;
	}

	/* Initializing values for the source vertex */
	vertexStatus[sourceVertex - 1]		= NODE_INTREE;
	bandwidthVector[sourceVertex - 1]	= 0;

	adjListNode** adjacencyList		= g->getAdjacencyList();
	adjListNode* sourceNeighborList = adjacencyList[sourceVertex - 1]; 
	adjListNode* temp = sourceNeighborList->next;
	int neighborVertexNumber;
	float edgeWeight;
	while( temp != NULL)
	{
		neighborVertexNumber = temp->nodeVal;
		edgeWeight           = temp->edgeWeight;
		vertexStatus[neighborVertexNumber - 1]	  = NODE_FRINGE;
		bandwidthVector[neighborVertexNumber - 1] = edgeWeight;
		parentVector[neighborVertexNumber - 1]    = sourceVertex;
		temp = temp->next;

		// Insert into heap
		heapNode hNode;
		hNode.key	= neighborVertexNumber;
		hNode.value = edgeWeight;
		h->insertElement(hNode);
		
	}
	for (int i = 0; i < vertexCount; i++)
	{
		if (!h->getHeapCurrentSize())
		{
			// No more fringes to process, so return
			return;
		}
		float maxVal;
		heapNode maximumNode;
		int maximumFlowVertexIndex = 0, j = 0;
		maximumNode = h->getMaximum();
		h->deleteRoot();
		maxVal = maximumNode.value;
		maximumFlowVertexIndex = maximumNode.key - 1;

		vertexStatus[maximumFlowVertexIndex] = NODE_INTREE;
		adjListNode* neighborList = adjacencyList[maximumFlowVertexIndex]->next;
		adjListNode* tempNode     = neighborList;
		int neighborVertex, neighborEdgeWeight;
		while (tempNode != NULL)
		{
			neighborVertex		= tempNode->nodeVal;
			neighborEdgeWeight	= tempNode->edgeWeight;
			switch (vertexStatus[neighborVertex - 1])
			{
				case NODE_UNSEEN:
					vertexStatus[neighborVertex - 1]	= NODE_FRINGE;
					bandwidthVector[neighborVertex - 1] = getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight);
					parentVector[neighborVertex - 1]    = maximumFlowVertexIndex + 1;

					// Insert into heap
					heapNode hNode;
					hNode.key	= neighborVertex;
					hNode.value = bandwidthVector[neighborVertex - 1];
					h->insertElement(hNode);
					break;

				case NODE_FRINGE:
					if (bandwidthVector[neighborVertex - 1] < getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight))
					{
						bandwidthVector[neighborVertex - 1] = getMinimum(bandwidthVector[maximumFlowVertexIndex], neighborEdgeWeight);
						parentVector[neighborVertex - 1]    = maximumFlowVertexIndex + 1;
						
						// Delete the node from the heap and re-insert with the updated bandwidth value
						float updatedVal =  bandwidthVector[neighborVertex - 1];
						h->deleteElement(neighborVertex);
						heapNode hNode;
						hNode.key	= neighborVertex;
						hNode.value = updatedVal;
						h->insertElement(hNode);
					}

					break;
			}
			tempNode = tempNode->next;
		}
	}
}

typedef pair<int, int> Pair;
typedef map<Pair, float > edgeToWeightMap;
typedef map<int, Pair > edgeMap;
edgeToWeightMap edgeWeightMap;
edgeMap			eMap;

float runMaxBWPathKruskal(Graph *g, int sourceVertex, int destVertex, int* pathVector)
{
	/* Create a sorted ordering of edges first */
	float runTime;
	adjListNode** adjList = g->getAdjacencyList();
	int vertexCount		  = g->getNumberOfVertices();
	heapNode hNode;
	int heapSize		  = g->getNumberOfEdges() + 1;
	Heap *h				  = new Heap(heapSize);

	Pair edge;
	int key = 0;
	int numberOfEdges = 0;

	for(int i = 0; i < vertexCount; i++)
	{
		//cout << i << endl;
		adjListNode* neighborList = adjList[i]->next;
		adjListNode* temp		  = neighborList;
		while(temp != NULL)
		{
			edge = make_pair(i+1, temp->nodeVal);
			if((edgeWeightMap.find(edge) == edgeWeightMap.end()) && (edgeWeightMap.find(swapPairContent(edge)) == edgeWeightMap.end()))
			{
				key++;
				numberOfEdges++;
				hNode.key			= key;
				hNode.value			= temp->edgeWeight;
				h->insertElement(hNode);
				eMap[key]		    = edge;
				edgeWeightMap[edge] = temp->edgeWeight;
			}
			temp = temp->next;
		}	
	}

	/* The following implements Kruskal's algorithm */
	// Sort the edges by their weight
	clock_t t1, t2;
	float runningTime;
	t1 = clock();
	h->heapSort();
	heapNode* heapArray = h->getHeapArray();
	Graph *maxSpanningTree = new Graph(vertexCount);
	maxSpanningTree->makeVertexSets();
	int *rankVector	  = new int[vertexCount];
	int *parentVector = new int[vertexCount];
	for (int i = 1; i <= vertexCount; i++)
	{
		makeSet(i, parentVector, rankVector);
	}
	for(int i = numberOfEdges-1; i >= 0; i--)
	{
		// Get the largest weight edge from the heap-sorted array
		Pair edge = eMap[heapArray[i].key];
		int v1 = edge.first;
		int v2 = edge.second;
		int r1 = findSet(v1, parentVector);
		int r2 = findSet(v2, parentVector);
		if (r1 != r2)
		{
			maxSpanningTree->addEdge(v1, v2, heapArray[i].value);
			doUnion(r1, r2, rankVector, parentVector);
		}

	}

	breadthFirstSearch(maxSpanningTree, sourceVertex, destVertex, pathVector);

	t2 = clock();
	runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
	
	delete maxSpanningTree;
	delete h;

	return runningTime;
	
}
