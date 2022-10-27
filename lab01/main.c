#include <stdio.h>
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

    while (!feof(f_in))
    {
        fgets(c, DIM, f_in);
        fputs(c, f_out);
        printf("%s", c);
    }

    fclose(f_in);
    fclose(f_out);
}

int main(int argc, char *argv[])
{
    parte1(argv[1], argv[2]);
    return 0;
}