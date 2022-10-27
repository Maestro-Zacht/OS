#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void create_2_son()
{
    pid_t pid1, pid2;

    if (pid1 = fork())
    {
        pid2 = fork();
    }

    if (pid1 != 0 && pid2 != 0)
    {
        printf("%d Exiting\n", getpid());
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        return 1;
    int n = atoi(argv[1]), t = atoi(argv[2]), i;

    for (i = 0; i < n; i++)
        create_2_son();

    sleep(t);
    printf("%d son ended\n", getpid());

    return 0;
}