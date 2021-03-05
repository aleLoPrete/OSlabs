#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 101

FILE *fp1, *fp2;
char line[102];
int flag;

sem_t semR, semW, semI;

void *reader(void *arg);
void invert();
void *inverter(void *arg);
void *writer(void *arg);

int main(int argc, char **argv)
{
    char line[101];
    pthread_t t_reader, t_inverter, t_writer;
    flag = 1;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");

    if (fp2 == NULL || fp1 == NULL)
    {
        return -1;
    }

    sem_init(&semR, 0, 1);
    sem_init(&semW, 0, 0);
    sem_init(&semI, 0, 0);

    pthread_create(&t_reader, NULL, reader, NULL);
    pthread_create(&t_writer, NULL, writer, NULL);
    pthread_create(&t_inverter, NULL, inverter, NULL);

    pthread_join(t_reader, NULL);
    return 0;
}

void *reader(void *arg)
{
    printf("started reader \n");
    while (fscanf(fp1, "%s", line) != EOF)
    {
        printf("reading lie %s \n", line);
        sem_wait(&semR);
        sem_post(&semI);
    }
    flag = 0;
    pthread_exit(NULL);
}

void *inverter(void *arg)
{
    printf("started inverter \n");
    while (1)
    {
        printf("interting lie %s \n", line);
        sem_wait(&semI);
        invert(line);
    }
    pthread_exit(NULL);
}

void *writer(void *arg)
{
    printf("started writer \n");
    while (1)
    {
        printf("weirint %s \n ", line);
        sem_wait(&semW);
        fprintf(fp2, "%s\n", line);
        sem_post(&semR);
    }
    pthread_exit(NULL);
}

void invert(char *string)
{
    char inverted[SIZE];
    int size = 0;

    while (string[size] != '\0')
        size++;

    for (int i = 0, j = size; i <= size; i++, j--)
    {
        inverted[i] = string[j];
    }
    string = inverted;
}