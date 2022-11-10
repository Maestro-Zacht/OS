#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int fd;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            fprintf(stderr, "Error with file\n");
            exit(-1);
        }
    }
    else
    {
        fprintf(stdout, "Arguments incorrect!\n");
    }

    return 0;
}