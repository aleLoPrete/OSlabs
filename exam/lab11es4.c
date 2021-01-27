#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

struct threadData
{
    int arr[20];
    int l;
    int h;
};

// è tutto sbalgiato perchè quando lavoro sui dati con i thread in modo ricorsivo copio la struttura per evitare delle
// race condition ma in questo modo non so come restituire il vettore, l'idea principale non sembra essere sbagliata
// ma in questo momento non funziona nulla
void mergeSort(void *data)
{
    struct threadData *copyOfData;
    memcpy(&copyOfData, data, sizeof(struct threadData));
    int tmp;

    int high = copyOfData->h;
    int highSx = copyOfData->h / 2;
    int lowRx = (copyOfData->h / 2) + 1;

    if ((copyOfData->h - copyOfData->l) == 1)
    {
        if (copyOfData->arr[0] > copyOfData->arr[1])
        {
            tmp = copyOfData->arr[1];
            copyOfData->arr[1] = copyOfData->arr[0];
            copyOfData->arr[0] = tmp;
        }
        return;
    }

    // thread 1 working on vector sx
    copyOfData->h = highSx;
    pthread_t t1;

    pthread_create(&t1, NULL, (void *)mergeSort, (void *)copyOfData);

    // thread 2 working on vector rx
    copyOfData->l = lowRx;
    copyOfData->h = high;

    pthread_t t2;

    pthread_create(&t2, NULL, (void *)mergeSort, (void *)copyOfData);

    //waiting fro two process to finish
    pthread_join(t1, t2);

    //merging two sorted vectors
    int sortedArray[high + 1];
    int k = 0;

    for (int i = 0, j; i < lowRx; i++)
    {
        j = i + lowRx;
        if (copyOfData->arr[i] > copyOfData->arr[j])
        {
            sortedArray[k] = copyOfData->arr[j];
            k++;
            sortedArray[k] = copyOfData->arr[i];
            k++;
        }
        else
        {
            sortedArray[k] = copyOfData->arr[i];
            k++;
            sortedArray[k] = copyOfData->arr[j];
            k++;
        }
    }

    for (int i = 0; i < high + 1; i++)
    {
        copyOfData->arr[i] = sortedArray[i];
    }
    return;
}

int main()
{
}