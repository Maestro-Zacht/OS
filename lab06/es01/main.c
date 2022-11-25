#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void genera_interi(int n, int fd_write)
{
    int num, fd[2], *buff;
    if (n <= 1)
    {
        num = 0;
        write(fd_write, &num, sizeof(int));
        num = 1;
        write(fd_write, &num, sizeof(int));
    }
    else
    {
        if (pipe(fd) == -1)
        {
            fprintf(stderr, "Error in creating pipe\n");
            exit(-1);
        }

        if (fork())
        {
            close(fd[1]);
            buff = (int *)malloc(n * sizeof(int));

            while (read(fd[0], buff + 1, (n - 1) * sizeof(int)) > 0)
            {
                buff[0] = 0;
                write(fd_write, buff, n * sizeof(int));
                buff[0] = 1;
                write(fd_write, buff, n * sizeof(int));
            }

            close(fd[0]);
            free(buff);
            wait(NULL);
        }
        else
        {
            close(fd[0]);
            genera_interi(n - 1, fd[1]);
            close(fd[1]);
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    int n, i, fd[2], *buf;
    if (argc == 2)
    {
        n = atoi(argv[1]);

        if (pipe(fd) == -1)
        {
            fprintf(stderr, "Error in creating pipe\n");
            exit(-1);
        }

        if (fork())
        {
            close(fd[1]);
            buf = (int *)malloc(n * sizeof(int));

            while (read(fd[0], buf, n * sizeof(int)) > 0)
            {
                for (i = 0; i < n; i++)
                {
                    fprintf(stdout, "%d", buf[i]);
                }
                fprintf(stdout, "\n");
            }

            close(fd[0]);
            free(buf);
            wait(NULL);
        }
        else
        {
            close(fd[0]);
            genera_interi(n, fd[1]);
            close(fd[1]);
            exit(0);
        }
    }
    else
    {
        fprintf(stderr, "Usage: main <n>\n");
    }
    return 0;
}