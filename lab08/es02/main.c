#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXSLEEPTIME 10
#define NSEM 5

void semaph_init(int S[2])
{
    if (pipe(S) == -1)
    {
        fprintf(stderr, "Error creating semaphore\n");
        exit(-1);
    }
}

void semaph_signal(int S[2])
{
    char c = 'c';
    if (write(S[1], &c, sizeof(char)) != 1)
    {
        fprintf(stderr, "Error signaling\n");
        exit(-1);
    }
}

void semaph_wait(int S[2])
{
    char c;
    if (read(S[0], &c, sizeof(char)) != 1)
    {
        fprintf(stderr, "Error waiting\n");
        exit(-1);
    }
}

void semaph_destroy(int S[2])
{
    close(S[0]);
    close(S[1]);
}

void T(char c)
{
    // srand(time(NULL));
    fprintf(stdout, "Executing %c on PID %d\n", c, getpid());
    sleep((rand() % MAXSLEEPTIME) + 1);
    fprintf(stdout, "%c done executing\n", c);
}

int main()
{
    int Sem[NSEM][2], i;

    for (i = 0; i < NSEM; i++)
        semaph_init(Sem[i]);

    if (!fork())
    {
        T('A');
        semaph_signal(Sem[0]);
        semaph_signal(Sem[0]);
        semaph_signal(Sem[0]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[0]);
        T('B');
        semaph_signal(Sem[1]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[0]);
        T('C');
        semaph_signal(Sem[2]);
        semaph_signal(Sem[2]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[0]);
        T('D');
        semaph_signal(Sem[3]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[2]);
        T('E');
        semaph_signal(Sem[4]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[2]);
        T('F');
        semaph_signal(Sem[4]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[4]);
        semaph_wait(Sem[4]);
        T('G');
        semaph_signal(Sem[1]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[3]);
        T('H');
        semaph_signal(Sem[1]);
        exit(0);
    }

    if (!fork())
    {
        semaph_wait(Sem[1]);
        semaph_wait(Sem[1]);
        semaph_wait(Sem[1]);
        T('I');
        exit(0);
    }

    while (wait(NULL) != -1)
        ;

    return 0;
}