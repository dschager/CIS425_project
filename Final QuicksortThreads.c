#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int* arr;
    int left;
    int right;
} ThreadData;	//check struct notes to make sure correct

int active = 0;

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//find pivot (end of array), determin what left and right based off pivot
int Partition(int* data, int left, int right) {
    int pivot = data[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (data[j] <= pivot) {
            i++;
            Swap(&data[i], &data[j]);
        }
    }

    Swap(&data[i + 1], &data[right]);
    return i + 1;
}


void* QuickSortThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;    //define data and what is considered left/right of pivot
    int left = data->left;
    int right = data->right;
    int* arr = data->arr;

    if (left < right) {
        int pivot = Partition(arr, left, right);

        pthread_t thread_left, thread_right;
        int left_created = 0, right_created = 0;

        //sort left of pivot and create thread
        if (left < pivot - 1) {
            if (active < 5) {
                active++;
                printf("Creating left thread. Active threads: %d\n", active);
                ThreadData* left_data = (ThreadData*)malloc(sizeof(ThreadData));
                left_data->arr = arr;
                left_data->left = left;
                left_data->right = pivot - 1;
                pthread_create(&thread_left, NULL, QuickSortThread, left_data);
                left_created = 1;
            } else {
                //otherwise, sort in current
                QuickSortThread((void*)&(ThreadData){arr, left, pivot - 1});
            }
        }

        //sort right of pivot and create new thread if needed
        if (pivot + 1 < right) {
            if (active < 5) {
                active++;
                printf("Creating right thread. Active threads: %d\n", active);
                ThreadData* right_data = (ThreadData*)malloc(sizeof(ThreadData));
                right_data->arr = arr;
                right_data->left = pivot + 1;
                right_data->right = right;
                pthread_create(&thread_right, NULL, QuickSortThread, right_data);
                right_created = 1;
            } else {
                //otherwise, sort in current
                QuickSortThread((void*)&(ThreadData){arr, pivot + 1, right});
            }
        }

        //wait for threads, then print when a thread ends
        if (left_created) {
            pthread_join(thread_left, NULL);
            active--;  // Decrement after thread finishes
            printf("Left thread finished. Active threads: %d\n", active);
        }
        if (right_created) {
            pthread_join(thread_right, NULL);
            active--;  // Decrement after thread finishes
            printf("Right thread finished. Active threads: %d\n", active);
        }
    }

    return NULL;
}

void QuickSort(int* arr, int size) {
    ThreadData* data = (ThreadData*)malloc(sizeof(ThreadData));	
    data->arr = arr;
    data->left = 0;
    data->right = size - 1;

    pthread_t main_thread;
    pthread_create(&main_thread, NULL, QuickSortThread, data);
    pthread_join(main_thread, NULL);

    //free memory when thread done
    free(data);
}

//print array
void PrintArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

#define ARRAY_SIZE 1000

//random array
void GenerateRandomArray(int* arr, int size) {
    srand(time(NULL));  // Seed the random number generator only once
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; 
    }
}

int main() {
    int arr[ARRAY_SIZE];
    GenerateRandomArray(arr, ARRAY_SIZE);
    
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    PrintArray(arr, size);

    clock_t start=clock();
    QuickSort(arr, size);  
    clock_t stop=clock();
    printf("Time : %f \n",(double)(stop-start)/CLOCKS_PER_SEC);

    printf("Sorted array:\n");
    PrintArray(arr, size);

    return 0;
}
