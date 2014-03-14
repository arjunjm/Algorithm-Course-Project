#define NULL 0

struct adjListNode
{
	int nodeVal;
	int nodeDegree;
	float edgeWeight;
	adjListNode* next;
};

void addToListEnd(adjListNode* listHead, int nodeValue, float edgeWeight);