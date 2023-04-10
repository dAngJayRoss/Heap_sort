#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

  // Function to swap the the position of two elements
  void swap(int *a, int *b) 
  {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
  
  void heapify(int *arr, int n, int i) 
  {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
    {
      largest = left;
    }
  
    if (right < n && arr[right] > arr[largest])
    {
      largest = right;
    }
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) 
    {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int *arr, int n)
{
  // Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    {
      heapify(arr, n, i);
    }
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) 
    {
      swap(&arr[0], &arr[i]);
  
      // Heapify root element to get highest element at root again
      heapify(arr, i, 0);
    }
}


//Helper merge function for mergesort.
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int* Larr = (int*)malloc(n1 * sizeof(int));
	int* Rarr = (int*)malloc(n2 * sizeof(int));

	extraMemoryAllocated = (n1 * sizeof(int)) + (n2 * sizeof(int));

	for (i = 0; i < n1; i++)
		Larr[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		Rarr[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (Larr[i] <= Rarr[j])
		{
			arr[k] = Larr[i];
			i++;
		}
		else
		{
			arr[k] = Rarr[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		arr[k] = Larr[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = Rarr[j];
		j++;
		k++;
	}

	free(Larr);
	free(Rarr);
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
  if (l < r)
	{
		int m = (l + r) / 2;

		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);

		merge(pData, l, m, r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

//Printing the array.
void printArray(int *ar, int sz)
{
  if(sz < 100)
  {
    printf("Data:\n");
    for(int i = 0; i < sz; ++i)
    {
      if(i == 0)
      {
        printf("%d ", ar[i]);
      }
      else if(i != 0 && i % 10)
      {
        printf("%d ", ar[i]);
      }
      else
      {
        printf("%d\n", ar[i]);
      }
    }
  }
  else
  {
    int i, s = sz - 100;
  	printf("Data:\n");
  	for (i=0;i<100;++i)
    	{
    		printf("%d ",ar[i]);
    	}
  	printf("\n\n");
  	
  	for (i=s;i < sz;++i)
    	{
    		printf("%d ",ar[i]);
    	}
  	printf("\n\n");
  }
    printf("\n");
}

int main(void)
{
	clock_t start, end;
	int i;
  double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("\n\n---------------------------");
		printf("\nDataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("runtime\t\t\t: %.1lf\n",cpu_time_used);
		printf("extra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
