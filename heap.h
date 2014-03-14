class Heap
{
	int heapMaxSize;
	int heapCurrentSize;
	float *heapArray;

public:

	/* Heap Constructor */
	Heap(int size);

	/* Heap Destructor */
	~Heap();

	/* Heap Index Functions */
	int getParent(int i);
	int getLeft(int i);
	int getRight(int i);

	/* Heap Building Functions */
	void  minHeapify(int i);
	void  buildMinHeap();

	/* Heap Operations */
	float getMinimum();
	void  insertElement(float value);
	void  deleteRoot();

	/* Misc Helper Functions */
	void  printHeapArray();
	int   getHeapCurrentSize();
};