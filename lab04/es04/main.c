#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define PIDFILE "pidfile"
#define DATAFILE "data.txt"
#define MAXSTR 4096

void exitHandler(int sig)
{
    exit(0);
}

void consumerHandler(int sig)
{
    char c;
    FILE *fd = fopen(DATAFILE, "r");

    while ((c = fgetc(fd)) != EOF)
        fprintf(stdout, "%c", toupper(c));

    fclose(fd);

    fprintf(stdout, "\n");
}

void producerHandler(int sig)
{
    return;
}

void consumer(pid_t producer_pid)
{
    int pidfile = open(PIDFILE, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IROTH);
    pid_t pid = getpid();

    write(pidfile, &pid, sizeof(pid_t));

    close(pidfile);

    signal(SIGUSR1, consumerHandler);
    signal(SIGUSR2, exitHandler);

    while (1)
    {
        pause();
        kill(producer_pid, SIGUSR1);
    }
}

void producer()
{
    int pidfile;
    pid_t consumer_pid;
    char str[MAXSTR];
    FILE *datafile;

    sleep(1);

    pidfile = open(PIDFILE, O_RDONLY);

    read(pidfile, &consumer_pid, sizeof(pid_t));

    close(pidfile);

    signal(SIGUSR1, producerHandler);

    fprintf(stdout, "Inserire stringa: ");

    while (fscanf(stdin, "%s", str) == 1)
    {
        if (strcmp(str, "end") == 0)
        {
            kill(consumer_pid, SIGUSR2);
            exit(0);
        }
        datafile = fopen(DATAFILE, "w");
        fprintf(datafile, "%s", str);
        fclose(datafile);

        kill(consumer_pid, SIGUSR1);
        pause();

        fprintf(stdout, "Inserire stringa: ");
    }
}

int main()
{
    pid_t producer_pid;

    setbuf(stdout, NULL);

    if (producer_pid = fork())
    {
        if (fork())
        {
            while (wait((int *)0) != -1)
                ;
        }
        else
        {
            consumer(producer_pid);
        }
    }
    else
    {
        producer();
    }
}