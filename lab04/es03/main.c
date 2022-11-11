#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define NSEC 1

void fatherHandler(int sig)
{
    fprintf(stdout, "Father Woke-up\n");
    sleep(NSEC);
}

void childHandler(int sig)
{
    fprintf(stdout, "Child Woke-up\n");
    sleep(NSEC);
}

int main()
{
    pid_t pid;
    int i;

    if (pid = fork())
    {
        signal(SIGUSR1, fatherHandler);
        sleep(NSEC);

        while (1)
        {
            kill(pid, SIGUSR2);
            pause();
        }
    }
    else
    {
        pid = getppid();
        signal(SIGUSR2, childHandler);

        while (1)
        {
            pause();
            kill(pid, SIGUSR1);
        }
    }
    return 0;
}
