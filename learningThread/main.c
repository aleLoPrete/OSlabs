#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

void *myturn(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        printf("My turn\n");
    }
    return NULL;
}

int main()
{
    pthread_t thread;

    pthread_create(&thread, NULL, myturn, NULL);

    printf("your turn");
    sleep(1);
    return 1;
}