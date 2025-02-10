#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern void assembler_function(char*,int);

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

int main(){
   char *text1 = "input.txt";
   clock_t start=clock();
   
    int arr[] = {34, 7, 23, 32, 5, 62, 32, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    PrintArray(arr, size);

    QuickSortIterative(arr, size);

    printf("Sorted array:\n");
    PrintArray(arr, size);

   clock_t stop=clock();

   //printf("%d %f\n",(int)stop,((float)stop)/CLOCKS_PER_SEC);
   printf("Time : %f \n",(double)(stop-start)/CLOCKS_PER_SEC);

   return 0;
}
