#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int p1[2], p2[2];
    int flag = 1;

    pipe(p1);
    pipe(p2);

    int pid = fork();

    if (pid != 0)
    { // parent
        while (1)
        {
            close(p2[0]);

            close(p1[1]);

            sleep(1);
            fprintf(stdout, "Father: %d\n", getpid());
            fflush(stdout);

            write(p2[1], &flag, sizeof(int)); // "signal" child
            //close(p2[1]);
            read(p1[0], &flag, sizeof(int)); // wait from child to write into p1
        }
    }
    else
    { // child
        while (1)
        {
            close(p1[0]);
            close(p2[1]);

            read(p2[0], &flag, sizeof(int)); // wait parent

            sleep(1);
            fprintf(stdout, "Child:%d\n", getpid());
            fflush(stdout);

            write(p1[1], &flag, sizeof(int)); // signal father
            //close(p2[0]
        }
    }

    return 1;
}