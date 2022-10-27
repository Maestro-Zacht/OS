#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DIM 256

void parte1(char *f_name1, char *f_name2)
{
    char c[DIM];
    FILE *f_in = fopen(f_name1, "r");
    FILE *f_out = fopen(f_name2, "w");

    if (f_in == NULL)
    {
        printf("Non valido\n");
    }

    while (fgets(c, DIM, f_in) != NULL)
    {
        fputs(c, f_out);
        printf("%s", c);
    }

    fclose(f_in);
    fclose(f_out);
}

void parte4(char *f_name1, char *f_name2)
{
    char buf[DIM];
    int f_in = open(f_name1, O_RDONLY);
    int f_out = open(f_name2, O_WRONLY | O_CREAT | O_TRUNC);
    int nr, nw;
    if (f_in == -1 || f_out == -1)
    {
        printf("Error with files\n");
        exit(1);
    }

    while ((nr = read(f_in, buf, DIM)) > 0)
    {
        nw = write(f_out, buf, nr);
        if (nw != nr)
        {
            fprintf(stderr, "Error writing\n");
        }
    }

    if (nr < 0)
    {
        fprintf(stderr, "Error reading\n");
    }

    close(f_in);
    close(f_out);
}

int main(int argc, char *argv[])
{
    if (argc >= 3)
    {
        // parte1(argv[1], argv[2]);
        parte4(argv[1], argv[2]);
    }
    return 0;
}