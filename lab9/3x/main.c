#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t semB, semC, semD, semE, semF, semG, semH, semI;

sem_init(semC, 0, 0);
sem_init(semB, 0, 0);
sem_init(semD, 0, 0);
sem_init(semE, 0, 0);
sem_init(semF, 0, 0);
sem_init(semG, 0, 0);
sem_init(semH, 0, 0);
sem_init(semI, 0, -3);

void A(void)
{
    sem_post(semB);
    sem_post(semC);
    sem_post(semD);
}

void B(void)
{
    sem_wait(semB);
    sem_post(semI);
}
void C(void)
{
    sem_wait(semC);
}
void D(void)
{
    sem_wait(semD);
}
void E(void)
{
}
void F(void)
{
}
void G(void)
{
    sem_wait(semG);
    sem_post(semI);
}
void H(void)
{
    sem_post(semI);
}
void I(void)
{
    sem_wait(semI); // initialized to -3
}

int main()
{
    pthead_create() :

                      return 0;
}