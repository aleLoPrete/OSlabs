#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

//sort array
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// takes vector from one file, print it  sorted on another file
void *sortFile(void *arg)
{

    char file[2][12] = (char **)arg; // array with file pointer

    FILE *input = fopen(file[0], "r");
    FILE *output = fopen(file[1], "w");

    int *array = malloc(10 * sizeof(int));

    int i = 0;
    while (fscanf(input, "%d", array[i]) != EOF)
    {
        i++;
        if (i > 9)
        {
            realloc(array, i * 2 * sizeof(int));
        }
    }

    quickSort(array, 0, i);

    for (int j = 0; j <= i; j++)
    {
        fprintf(output, "%d\n", array[j]);
    }

    return NULL;
}

int main()
{
}