/* 
Daniel Schager and Daniel Jackson
CIS425
19 February 2024
Project 1
*/

/* Iterative C program for merge sort */
// Obtained from https://www.geeksforgeeks.org/iterative-merge-sort/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<pthread.h>

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r);

// Utility function to find minimum of two integers
int min(int x, int y) { return (x<y)? x :y; }


/* Iterative mergesort function to sort arr[0...n-1] */
void mergeSort(int arr[], int n)
{
int curr_size; // For current size of subarrays to be merged
				// curr_size varies from 1 to n/2
int left_start; // For picking starting index of left subarray
				// to be merged

// Merge subarrays in bottom up manner. First merge subarrays of
// size 1 to create sorted subarrays of size 2, then merge subarrays
// of size 2 to create sorted subarrays of size 4, and so on.
for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
{
	// Pick starting point of different subarrays of current size
	for (left_start=0; left_start<n-1; left_start += 2*curr_size)
	{
		// Find ending point of left subarray. mid+1 is starting 
		// point of right
		int mid = min(left_start + curr_size - 1, n-1);

		int right_end = min(left_start + 2*curr_size - 1, n-1);

		// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
		merge(arr, left_start, mid, right_end);
	}
}
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
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
