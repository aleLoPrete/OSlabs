#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void printArr();
void allNBitNumbers();

int main()
{
    int n, arr[30], i = 0;
    printf("n:");
    scanf("%d", &n);
    allNBitNumbers(arr, i, n);

    return 0;
}

void printArr(int *a, int n)
{

    for (int i = 0; i < n; i++)
    {
        printf(" %d ", a[i]);
    }
    printf("\n");
    return;
}

void allNBitNumbers(int *arr, int i, int n)
{
    int pid;

    if (i == n)
    {
        printArr(arr, n);
        return;
    }

    arr[i] = 0;
    allNBitNumbers(arr, i + 1, n);
    arr[i] = 1;
    allNBitNumbers(arr, i + 1, n);

    return;
}