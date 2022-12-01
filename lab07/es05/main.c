#include <unistd.h>

int main()
{
    if (!fork())
        sleep(60);

    return 0;
}