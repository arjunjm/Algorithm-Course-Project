#include "maxBWpath.h"
#include <iostream>
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
		parentVector[neighborVertexNumber - 1]   = sourceVertex;
		temp = temp->next;
	}

	for (int i = 0; i < vertexCount; i++)
	{
		int maximum;
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

void runMaxBWPathDijkstraWithHeap(Graph g, int sourceVertex, int destVertex)
{

}

void runMaxBWPathKruskal(Graph g, int sourceVertex, int destVertex)
{

}