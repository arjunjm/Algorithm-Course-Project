#include "maxBWpath.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>

using namespace std;

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

void runMaxBWPathKruskal(Graph *g, int sourceVertex, int destVertex, int* parentVector, float* bandwidthVector)
{
	/* Create a sorted ordering of edges first */
	adjListNode** adjList = g->getAdjacencyList();
	int vertexCount		  = g->getNumberOfVertices();

	typedef pair<int, int> Pair;
	typedef std::unordered_map<Pair, float, pairHasher > edgeToWeightMap;
	typedef map<int, Pair > edgeMap;
	edgeToWeightMap edgeWeightMap;
	edgeMap			eMap;
	heapNode		hNode;
	Heap *h			= new Heap(vertexCount^2);

	Pair edge;
	int key = 0;
	int numberOfEdges = 0;

	for(int i = 0; i < vertexCount; i++)
	{
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
	/*
	//Print Map
	edgeMap::iterator it;
	for (it = eMap.begin(); it != eMap.end(); it++)
	{
		Pair edge = it->second;
		cout << it->first << " : (" << edge.first << ", " << edge.second << ")";
		cout << endl;
	}

	//Print edgeWeightMap
	edgeToWeightMap::iterator iter;
	for (iter = edgeWeightMap.begin(); iter != edgeWeightMap.end(); iter++)
	{
		Pair edge = iter->first;
		cout << "( " << edge.first << ", " << edge.second << ")" << ": " << iter->second;
		cout << endl;
	}

	//Print heap elements increasing order
	heapNode maximum;
	/*while ( h->getHeapCurrentSize() )
	{
		maximum = h->getMaximum();
		h->deleteRoot();
		cout << maximum.value << '\t';
	}*/

	// Sort the edges by their weight
	h->heapSort();
	heapNode* heapArray = h->getHeapArray();
	for(int i = numberOfEdges-1; i >= 0; i--)
	{
		cout << heapArray[i].value << ": (" << (eMap[heapArray[i].key]).first << ", " << (eMap[heapArray[i].key]).second << ")" << '\t' ;
	}
	cout << endl;
	

	delete h;
}