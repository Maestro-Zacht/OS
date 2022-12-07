#include <unistd.h>
#include <sys/wait.h>

int main()
{
    if (fork())
        sleep(60);

    wait(NULL);
    return 0;
}