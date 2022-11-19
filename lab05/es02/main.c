#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int pipef[2], pipec[2];

void ctrlcHandler(int sig)
{
    char c = 'e';
    write(pipef[1], &c, sizeof(char));
    exit(0);
}

int main()
{
    int i;
    char c;
    if (pipe(pipef) == -1 || pipe(pipec) == -1)
    {
        fprintf(stderr, "Error creating pipes\n");
    }
    else if (fork())
    {
        // Father
        close(pipef[0]);
        close(pipec[1]);
        // signal(SIGINT, ctrlcHandler);
        signal(SIGCHLD, SIG_IGN);
        do
        {
            fprintf(stdout, "I'm the father (PID = %d)\n", getpid());
            c = 'c';
            write(pipef[1], &c, sizeof(char));

            read(pipec[0], &c, sizeof(char));
        } while (c == 'c');

        close(pipef[1]);
        close(pipec[0]);
    }
    else
    {
        close(pipef[1]);
        close(pipec[0]);

        do
        {
            read(pipef[0], &c, sizeof(char));
            if (c == 'c')
            {
                fprintf(stdout, "I'm the child (PID = %d)\n", getpid());
                c = 'c';
                write(pipec[1], &c, sizeof(char));
            }
        } while (c == 'c');

        close(pipef[0]);
        close(pipec[1]);
    }
    return 0;
}