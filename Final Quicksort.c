#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000  // Define array size

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* data, int left, int right) {
    int x = data[right];  // Pivot element
    int i = (left - 1);

    for (int j = left; j <= right - 1; ++j) {
        if (data[j] <= x) {
            ++i;
            Swap(&data[i], &data[j]);
        }
    }

    Swap(&data[i + 1], &data[right]);
    return (i + 1);
}

void QuickSortIterative(int* data, int count) {
    if (count <= 1) return; // No need to sort

    int startIndex = 0, endIndex = count - 1;
    int top = -1;
    int* stack = (int*)malloc(sizeof(int) * count);

    stack[++top] = startIndex;
    stack[++top] = endIndex;

    while (top >= 0) {
        endIndex = stack[top--];
        startIndex = stack[top--];

        int p = Partition(data, startIndex, endIndex);

        if (p - 1 > startIndex) {
            stack[++top] = startIndex;
            stack[++top] = p - 1;
        }

        if (p + 1 < endIndex) {
            stack[++top] = p + 1;
            stack[++top] = endIndex;
        }
    }

    free(stack);
}

void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Generate random array
void GenerateRandomArray(int* arr, int size) {
    srand(time(NULL));  // Seed the random number generator only once
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;  // Random values between 0 and 999
    }
}

int main() {
    int arr[ARRAY_SIZE];
    GenerateRandomArray(arr, ARRAY_SIZE);
    
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    PrintArray(arr, size);

    clock_t start = clock();
    QuickSortIterative(arr, size);
    clock_t stop = clock();

    printf("Time: %f seconds\n", (double)(stop - start) / CLOCKS_PER_SEC);

    printf("Sorted array:\n");
    PrintArray(arr, size);

    return 0;
}
