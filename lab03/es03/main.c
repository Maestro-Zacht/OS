#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXBUF 4096
#define MAXROWS 256

int main(int argc, char *argv[])
{
    FILE *fd;
    char buf[MAXBUF], cmd[MAXBUF], params[MAXROWS][MAXBUF];
    int i, j;

    memset(buf, 0, sizeof(buf));
    memset(cmd, 0, sizeof(cmd));

    if (argc >= 2)
    {
        fd = fopen(argv[1], "r");

        /*while (fscanf(fd, " %s ", buf) == 1)
        {
            if (strcmp(buf, "end") == 0)
            {
                fprintf(stdout, "Executing with system: (%s)\n", cmd);
                system(cmd);
                memset(cmd, 0, sizeof(cmd));
            }
            else
            {
                sprintf(cmd, "%s %s", cmd, buf);
            }
        }

        fseek(fd, 0, SEEK_SET);*/

        i = 0;
        fscanf(fd, "%s", cmd);
        while (fscanf(fd, "%s", buf) == 1)
        {
            if (strcmp(buf, "end") == 0)
            {
                if (fork())
                {
                    sleep(3);
                    memset(cmd, 0, sizeof(cmd));
                    memset(params, 0, sizeof(params));
                    i = 0;
                }
                else
                {
                    fprintf(stdout, "Executing with exec: (%s ", cmd);
                    for (j = 0; j < i; j++)
                    {
                        fprintf(stdout, "%s ", params[j]);
                    }
                    fprintf(stdout, ")\n");
                    params[i] = NULL;
                    execvp(cmd, params);
                }
            }
            else
            {
                sprintf(params[i++], "%s", buf);
            }
        }
    }

    return 0;
}