#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void scambia(int fd, int pos)
{
    int a, b;
    off_t offset = sizeof(int) * (1 + pos);

    lseek(fd, offset, SEEK_SET);
    read(fd, &a, sizeof(int));
    read(fd, &b, sizeof(int));

    lseek(fd, offset, SEEK_SET);
    write(fd, (a > b) ? &b : &a, sizeof(int));
    write(fd, (a > b) ? &a : &b, sizeof(int));
}

int main(int argc, char const *argv[])
{
    int fd, i, j, n;
    pid_t pid, p_prec;
    if (argc == 2)
    {
        fprintf(stdout, "Opening file %s\n", argv[1]);
        fd = open(argv[1], O_RDWR | O_SYNC);
        if (fd == -1)
        {
            fprintf(stderr, "Error with file\n");
            exit(-1);
        }

        read(fd, &n, sizeof(int));

        for (i = 0; i < n; i++)
        {
            read(fd, &j, sizeof(int));
            fprintf(stdout, "%d\n", j);
        }

        fprintf(stdout, "\n");

        for (i = 0; i < n - 1; i++)
        {
            for (j = 0, p_prec = 0; j < n - 1 - i; j++)
            {
                if (p_prec != 0)
                {
                    waitpid(p_prec, (int *)0, 0);
                }
                pid = fork();
                if (!pid)
                {
                    scambia(fd, j);
                    exit(0);
                }
                p_prec = pid;
            }
            while (wait((int *)0) != -1)
                ;
        }

        lseek(fd, sizeof(int), SEEK_SET);
        for (i = 0; i < n; i++)
        {
            read(fd, &j, sizeof(int));
            fprintf(stdout, "%d\n", j);
        }

        close(fd);
    }
    else
    {
        fprintf(stderr, "Arguments incorrect!\n");
    }

    return 0;
}