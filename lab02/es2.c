#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void P(int i)
{
    printf("P%d, PID %d\n", i, getpid());
    sleep(2);
}

int main()
{
    P(1);
    if (fork())
    {
        // parent
        P(2);

        if (fork())
        {
            // parent
            P(4);
        }
        else
        {
            // son
            P(5);
            exit(1);
        }
        wait(NULL);
        P(7);
    }
    else
    {
        // son
        P(3);
        if (!fork())
        {
            // son
            P(6);
            exit(1);
        }
        wait(NULL);
        P(8);
        exit(1);
    }

    wait(NULL);
    P(9);

    return 0;
}