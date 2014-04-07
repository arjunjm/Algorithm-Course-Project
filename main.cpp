#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <time.h>
#include <list>
#include "graph.h"
#include "heap.h"
#include "maxBWpath.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << " Usage incorrect! Please specify the graph to generate and the number of iterations!! Exiting! \n";
		return 0;
	}
	
	clock_t t1, t2;
	float runningTime;

	Graph *randomGraph_1, *randomGraph_2, *graph;
	
	if (strcmp(argv[1], "1") == 0)
	{
		t1 = clock();
		cout << "Generating graph with 5000 vertices in which every vertex has degree 6!" << endl;
		do
		{
			
			randomGraph_1 = Graph::generateRandomGraph(5000, 6);

		} while (randomGraph_1 == NULL);
		t2 = clock();
		runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
		cout << "Graph generated in " << runningTime << " seconds " << endl;
		graph = randomGraph_1;
	}

	else if (strcmp(argv[1], "2") == 0)
	{
		t1 = clock();
		cout << "Generating graph with 5000 vertices in which every vertex has an edge to about 20 percent of the other vertices" << endl;
		randomGraph_2 = Graph::generateRandomGraph(5000, (float)0.2);
		t2 = clock();
		runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
		cout << " Graph generated in " << runningTime << " seconds " << endl;
		graph = randomGraph_2;
	}
	else
	{
		cout << "Arguments unknown! Exiting!!\n";
		return 0;
		cout << endl;
	}

    int numberOfIterations = atoi(argv[2]);
    srand(time(NULL));
    for (int i = 0 ; i < numberOfIterations; i++)
    {
        cout << endl;
        cout << "==========================================================\n";
        cout << "==========================================================\n";
        cout << "Generating new source-destination pairs! (Iteration : " << i+1 << ")";
        int sourceVertex, destVertex;
        int		vertexCount		 = graph->getNumberOfVertices();


        sourceVertex = rand() % vertexCount + 1;
        do
        {
            destVertex = rand() % vertexCount + 1;
        } while (destVertex == sourceVertex);

        cout << endl;
        cout << "Source Vertex = " << sourceVertex << endl;
        cout << "Destination Vertex = " << destVertex << endl << endl;

        // Algorithm #1
        t1 = clock();
        cout << "Calculating Maximum Bandwidth Path Using Dijkstra's Method without heap" << endl;
        cout << "=======================================================================" << endl;

        int		*pVector_1		   = new int[vertexCount];
        float   *bandwidthVector_1 = new float[vertexCount];

        runMaxBWPathDijkstraNoHeap(graph, sourceVertex, destVertex, pVector_1, bandwidthVector_1);

        // The stack is just used for ease in printing the path
        stack<int> vertexStack_1;

        vertexStack_1.push(destVertex);
        int vertex = pVector_1[destVertex - 1];
        do
        {
            vertexStack_1.push(vertex);
            if (vertex == sourceVertex)
                break;
            vertex = pVector_1[vertex - 1];
        } while (true);

        cout << "Max Bandwidth Path  :: ";
        while(!vertexStack_1.empty())
        {
            cout << vertexStack_1.top();
            if (vertexStack_1.top() != destVertex)
                cout << "-->";
            vertexStack_1.pop();
        }

        cout << endl;
        cout << endl;
        cout << "Max Bandwidth Value :: " << bandwidthVector_1[destVertex - 1] << endl;
        cout << endl;
        t2 = clock();
        runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
        cout << "Running time : " << runningTime << " seconds" << endl;

        cout << "---------------------------------------------------------------------------";
        cout << endl << endl << endl;

        delete pVector_1;
        delete bandwidthVector_1;


        // Algorithm #2
        t1 = clock();
        cout << "Calculating Maximum Bandwidth Path Using Dijkstra's Method with heap" << endl;
        cout << "====================================================================" << endl;

        int		*pVector_2		   = new int[vertexCount];
        float   *bandwidthVector_2 = new float[vertexCount];

        runMaxBWPathDijkstraWithHeap(graph, sourceVertex, destVertex, pVector_2, bandwidthVector_2);

        // The stack is just used for ease in printing the path
        stack<int> vertexStack_2;

        vertexStack_2.push(destVertex);
        int vertexVal = pVector_2[destVertex - 1];
        do
        {
            vertexStack_2.push(vertexVal);
            if (vertexVal == sourceVertex)
                break;
            vertexVal = pVector_2[vertexVal - 1];
        } while (true);

        cout << "Max Bandwidth Path  :: ";
        while(!vertexStack_2.empty())
        {
            cout << vertexStack_2.top();
            if (vertexStack_2.top() != destVertex)
                cout << "-->";
            vertexStack_2.pop();
        }

        cout << endl << endl;
        cout << "Max Bandwidth Value :: " << bandwidthVector_2[destVertex - 1] << endl << endl;
        t2 = clock();
        cout << endl;
        runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
        cout << "Running time : " << runningTime << " seconds" << endl;

        cout << "---------------------------------------------------------------------------";
        cout << endl << endl << endl;

        delete pVector_2;
        delete bandwidthVector_2;


        // Algorithm #3
        t1 = clock();
        cout << "Calculating Maximum Bandwidth Path Using Kruskal's Method" << endl;
        cout << "=========================================================" << endl;
        int *pVector_3			   = new int[vertexCount];
        float algorithmRunningTime = runMaxBWPathKruskal(graph, sourceVertex, destVertex, pVector_3);
        stack<int> vertexStack_3;
        int predecessorVertex = pVector_3[destVertex - 1];
        vertexStack_3.push(destVertex);

        int bandwidth = graph->getEdgeWeight(destVertex, predecessorVertex);
        int temp = 0;

        do
        {
            vertexStack_3.push(predecessorVertex);
            if (predecessorVertex == sourceVertex)
                break;
            temp = graph->getEdgeWeight(predecessorVertex, pVector_3[predecessorVertex - 1]);
            if (temp < bandwidth)
                bandwidth = temp;
            predecessorVertex = pVector_3[predecessorVertex - 1];	
        }while (true);

        cout << "Max Bandwidth Path  :: ";
        while(!vertexStack_3.empty())
        {
            cout << vertexStack_3.top();
            if (vertexStack_3.top() != destVertex)
                cout << "-->";
            vertexStack_3.pop();
        }

        cout << endl << endl;
        cout << "Max Bandwidth Value :: " << bandwidth << endl << endl;
        t2 = clock();
        cout << endl;
        runningTime = ((float) t2 - (float) t1) / CLOCKS_PER_SEC;
        cout << "Algorithm Running Time (excluding the time for data structure creation and intialization) : " << algorithmRunningTime << " seconds" <<endl;
        cout << "Total Running time : " << runningTime << " seconds" << endl;
        cout << "---------------------------------------------------------------------------";

        delete pVector_3;
        cout << endl << endl << endl;
    }	
	delete graph;

	cout << "Program done executing..Press any key to quit!" <<endl;
	return 1;
}
