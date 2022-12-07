#include <semaphore.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAXSLEEPTIME 10
#define NTHR 9

sem_t Sem[NTHR];

void T(char c)
{
    fprintf(stdout, "Executing %c\n", c);
    sleep((rand() % MAXSLEEPTIME) + 1);
    fprintf(stdout, "%c done executing\n", c);
}

void *A(void *p)
{
    while (1)
    {
        sem_wait(&Sem[0]);
        T('A');
        sem_post(&Sem[1]);
        sem_post(&Sem[2]);
        sem_post(&Sem[3]);
    }
    return NULL;
}

void *B(void *p)
{
    while (1)
    {
        sem_wait(&Sem[1]);
        T('B');
        sem_post(&Sem[4]);
    }
    return NULL;
}

void *C(void *p)
{
    while (1)
    {
        sem_wait(&Sem[2]);
        T('C');
        sem_post(&Sem[5]);
        sem_post(&Sem[6]);
    }
    return NULL;
}
void *D(void *p)
{
    while (1)
    {
        sem_wait(&Sem[3]);
        T('D');
        sem_post(&Sem[7]);
    }
    return NULL;
}

void *E(void *p)
{
    while (1)
    {
        sem_wait(&Sem[5]);
        T('E');
        sem_post(&Sem[8]);
    }
    return NULL;
}

void *F(void *p)
{
    while (1)
    {
        sem_wait(&Sem[6]);
        T('F');
        sem_post(&Sem[8]);
    }
    return NULL;
}

void *G(void *p)
{
    while (1)
    {
        sem_wait(&Sem[8]);
        sem_wait(&Sem[8]);
        T('G');
        sem_post(&Sem[4]);
    }
    return NULL;
}

void *H(void *p)
{
    while (1)
    {
        sem_wait(&Sem[7]);
        T('H');
        sem_post(&Sem[4]);
    }
    return NULL;
}

void *I(void *p)
{
    while (1)
    {
        sem_wait(&Sem[4]);
        sem_wait(&Sem[4]);
        sem_wait(&Sem[4]);
        T('I');
        sem_post(&Sem[0]);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t tid[NTHR];

    srand(time(NULL));

    sem_init(&Sem[0], 0, 1);
    for (i = 1; i < NTHR; i++)
        sem_init(&Sem[i], 0, 0);

    pthread_create(&tid[0], NULL, A, NULL);
    pthread_create(&tid[1], NULL, B, NULL);
    pthread_create(&tid[2], NULL, C, NULL);
    pthread_create(&tid[3], NULL, D, NULL);
    pthread_create(&tid[4], NULL, E, NULL);
    pthread_create(&tid[5], NULL, F, NULL);
    pthread_create(&tid[6], NULL, G, NULL);
    pthread_create(&tid[7], NULL, H, NULL);
    pthread_create(&tid[8], NULL, I, NULL);

    for (i = 0; i < NTHR; i++)
        pthread_detach(tid[i]);

    pause();

    return 0;
}