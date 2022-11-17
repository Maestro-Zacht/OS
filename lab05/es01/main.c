#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define MAXSTR 4096

void consumer(int pipe_read)
{
    char str[MAXSTR];
    int nchar, i;

    do
    {
        read(pipe_read, &nchar, sizeof(int));
        if (nchar != 0)
        {
            read(pipe_read, str, nchar);
            for (i = 0; i < nchar; i++)
                fprintf(stdout, "%c", toupper(str[i]));
            fprintf(stdout, "\n");
        }
    } while (nchar != 0);
}

void producer(int pipe_write)
{
    char str[MAXSTR];
    int len;

    do
    {
        fprintf(stdout, "Inserire stringa: ");
        fscanf(stdin, "%s", str);

        if (strcmp(str, "end") != 0)
        {
            len = strlen(str);
            write(pipe_write, &len, sizeof(int));
            write(pipe_write, str, len);
        }
        else
        {
            len = 0;
            write(pipe_write, &len, sizeof(int));
        }
    } while (strcmp(str, "end") != 0);
}

int main()
{
    int fd[2];

    setbuf(stdout, NULL);

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Errore creating pipe\n");
    }
    else if (fork())
    {
        if (fork())
        {
            while (wait((int *)0) != -1)
                ;
        }
        else
        {
            close(fd[1]);
            consumer(fd[0]);
            close(fd[0]);
        }
    }
    else
    {
        close(fd[0]);
        producer(fd[1]);
        close(fd[1]);
    }

    return 0;
}