/* 
Daniel Schager and Daniel Jackson
CIS425
19 February 2024
Project 1
Mergesort with Threads
*/

/* Iterative C program for merge sort */
// Obtained from https://www.geeksforgeeks.org/iterative-merge-sort/
//Please Note: All original comments were removed to improve readability

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>

void merge(int arr[], int l, int m, int r);

int min(int x, int y) { return (x<y)? x :y; }

//Creates a pointer to an array, along with left, mid, and right
typedef struct {
    int *arr;
    int left;
    int mid;
    int right;
} MergeParams;  

//runner function
void *mergeThread(void *args) {
	MergeParams *params = (MergeParams *) args;
	
	merge(params->arr, params->left, params->mid, params->right);
	free(params); //Frees the allocated memory for the MergeParams struct
	return NULL;
}




void mergeSort(int arr[], int n)
{
int curr_size; 
int left_start; 

int num_threads;
pthread_t threads[5]; //Declares up to 5 threads


for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
{
    num_threads = 0;

	for (left_start=0; left_start<n-1; left_start += 2*curr_size)
	{
		
		int mid = min(left_start + curr_size - 1, n-1);

		int right_end = min(left_start + 2*curr_size - 1, n-1);

        //Stops creating threads after max exceeded
        if (num_threads < 5) {
            //Creates a structure to hold the same parameters as the original method
            MergeParams *params = (MergeParams *) malloc(sizeof(MergeParams));
            params->arr = arr;
            params->left = left_start;
            params->mid = mid;
            params->right = right_end;

		//Creates a thread to perform merge
            pthread_create(&threads[num_threads], NULL, mergeThread, params);
            num_threads++;
        } else {
			//for if threads are maxed out
		    merge(arr, left_start, mid, right_end);
        }

		
	}
	//loops and joins threads together
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}
}

void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	int L[n1], R[n2];

	//int *L = (int *)malloc (n1 * sizeof(int));
    	//int *R = (int *)malloc (n2 * sizeof(int));
	

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];

	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}


	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}


void printArray(int A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}


int main()
{
	//Creates a clock with start' and 'end' variables
	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//n = size of array
	int n = 10000;
	
	//4 declared arrays
	int arr1[n], arr2[n], arr3[n], arr4[n];

	//populates arrays with random integers 1-999
	int i;
	for (i=0; i< 10000; i++) {
		arr1[i] = rand() % 1000;
		arr2[i] = rand() % 1000;
		arr3[i] = rand() % 1000;
		arr4[i] = rand() % 1000;
	}

	mergeSort(arr1, n);
	mergeSort(arr2, n);
	mergeSort(arr3, n);
	mergeSort(arr4, n);
	printf("All arrays complete\n");

	end = clock();
	cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
	printf("The threaded mergesort program took %f seconds.\n", cpu_time_used);
	
	return 0;
}
