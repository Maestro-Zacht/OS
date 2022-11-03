#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAXBUF 4096
#define MAXROWS 256

int main(int argc, char *argv[])
{
    FILE *fd;
    char buf[MAXBUF] = {0}, cmd[MAXBUF] = {0}, *params[MAXROWS], *token;
    int i, j;

    if (argc >= 2)
    {
        fd = fopen(argv[1], "r");

        while (fgets(cmd, MAXBUF, fd) != NULL)
        {
            cmd[strlen(cmd) - 1] = '\0';
            fprintf(stdout, "Executing with system: (%s)\n", cmd);
            system(cmd);
            memset(cmd, 0, sizeof(cmd));
        }

        fseek(fd, 0, SEEK_SET);

        while (fgets(buf, MAXBUF, fd) != NULL)
        {
            buf[strlen(buf) - 1] = '\0';
            i = 0;
            token = strtok(buf, " ");
            strcpy(cmd, token);
            while (token != NULL)
            {
                params[i++] = strdup(token);
                token = strtok(NULL, " ");
            }
            params[i] = NULL;

            if (fork())
            {
                sleep(3);
                memset(cmd, 0, sizeof(cmd));
                for (j = 0; j < i; j++)
                {
                    free(params[j]);
                }

                i = 0;
            }
            else
            {
                fprintf(stdout, "Executing with exec: (");
                for (j = 0; j < i; j++)
                {
                    fprintf(stdout, "%s ", params[j]);
                }
                fprintf(stdout, ")\n");
                params[i] = NULL;
                if (execvp(cmd, params) == -1)
                {
                    fprintf(stderr, "Error! %s\n", strerror(errno));
                    exit(-1);
                }
            }
        }
    }

    return 0;
}