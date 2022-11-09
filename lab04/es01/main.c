#include <stdio.h>

int main(int argc, char const *argv[])
{
    int num;

    fscanf(stdin, "%d", &num);
    while (num != 0)
    {
        fprintf((num % 2 == 0) ? stdout : stderr, "%d\n", num);
        fscanf(stdin, "%d", &num);
    }

    return 0;
}
