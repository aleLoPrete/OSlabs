#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int P1 = 0;
int P2 = 0;

void signalHandler1();
void signalHandler2();

int main()
{
    pid_t pidc1, pidc2;

    pidc1 = fork();

    if (pidc1 == 0)
    {
        //child1
        while (1)
        {
            fprintf(stdout, "C1!\n");
            sleep(1);
            kill(getppid(), SIGUSR1);
        }
        exit(1);
    }
    else
    {
        pidc2 = fork();
        if (pidc2 == 0)
        {
            while (1)
            {
                fprintf(stdout, "C1!\n");
                sleep(1);
                kill(getppid(), SIGUSR2);
            }
            exit(1);
            //child2
        }
        else
        {
            //parent
            signal(SIGUSR1, signalHandler1);
            signal(SIGUSR2, signalHandler2);
            while (1)
            {

                fflush(stdout);
                pause();
                fprintf(stdout, "Sono il papàaaaaaa \nP1=%d, P2=%d", P1, P2);
                if (P2 == 3 || P1 == 3)
                    break;
            }
            kill(pidc1, SIGINT);
            kill(pidc2, SIGINT);
        }
    }
    return 1;
}

void signalHandler1(int n)
{
    P1++;
    printf("from p1");
    return;
}

void signalHandler2(int n)
{
    P2++;
    printf("form p2");
    return;
}
