#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int outfile, n;
    FILE *infile;
    float c, x;

    if (argc == 3)
    {
        infile = fopen(argv[1], "r");
        outfile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);

        while (fscanf(infile, "%f %f %d", &c, &x, &n) == 3)
        {
            write(outfile, &c, sizeof(float));
            write(outfile, &x, sizeof(float));
            write(outfile, &n, sizeof(int));
        }

        fclose(infile);
        close(outfile);
    }

    return 0;
}