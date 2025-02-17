//
/* Iterative C program for merge sort */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>

void merge(int arr[], int l, int m, int r);

int min(int x, int y) { return (x<y)? x :y; }

//Creates a pointer an array, along with left, mid, and right
typedef struct {
    int *arr;
    int left;
    int mid;
    int right;
} MergeParams;  

void *mergeThread(void *args) {
	MergeParams *params = (MergeParams *) args;
	
	merge(params->arr, params->left, params->mid, params->right);
	free(params); //Frees the allocated memory for the MergeParams struct
	return NULL;
}



/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
int curr_size; // For current size of subarrays to be merged
				// curr_size varies from 1 to n/2
int left_start; // For picking starting index of left subarray
				// to be merged

int num_threads;
pthread_t threads[5]; //Declares up to 5 threads

// Merge subarrays in bottom up manner. First merge subarrays of
// size 1 to create sorted subarrays of size 2, then merge subarrays
// of size 2 to create sorted subarrays of size 4, and so on.
for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
{
    num_threads = 0;

	for (left_start=0; left_start<n-1; left_start += 2*curr_size)
	{
		
		int mid = min(left_start + curr_size - 1, n-1);

		int right_end = min(left_start + 2*curr_size - 1, n-1);

        //Stops creating threads after max exceeded
        if (num_threads < 5) {
            //Creates a structure to hold same parameters as original method
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
	//joins threads together
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
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

	/* Merge the temp arrays back into arr[l..r]*/
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

	/* Copy the remaining elements of L[], if there are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* Function to print an array */
void printArray(int A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

/* Driver program to test above functions */
int main()
{

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//size of array
	int n = 10000;
	int arr1[n], arr2[n], arr3[n], arr4[n];

	int i;
	for (i=0; i< 10000; i++) {
		arr1[i] = rand() % 1000;
		arr2[i] = rand() % 1000;
		arr3[i] = rand() % 1000;
		arr4[i] = rand() % 1000;
	}

	int n1 = sizeof(arr1)/sizeof(arr1[0]);
	int n2 = sizeof(arr2)/sizeof(arr2[0]);
	int n3 = sizeof(arr3)/sizeof(arr3[0]);
	int n4 = sizeof(arr4)/sizeof(arr4[0]);

	mergeSort(arr1, n);
	mergeSort(arr2, n);
	mergeSort(arr3, n);
	mergeSort(arr4, n);
	printf("All arrays complete");

	end = clock();
	cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
	printf("The threaded mergesort program took %f seconds.\n", cpu_time_used);
	
	return 0;
}
