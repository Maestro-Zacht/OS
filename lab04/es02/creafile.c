#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define N 7

int main()
{
    int fd = open("input", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IROTH);
    int vet[N] = {1, 4, 6, 5, 8, 32, 3}, num = N;

    write(fd, &num, sizeof(int));
    write(fd, vet, num * sizeof(int));

    close(fd);

    return 0;
}