#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 100

sem_t sem_buff1w, sem_buff1r, sem_buff2w, sem_buff2r;
char buff1[MAXLEN], buff2[MAXLEN];
int finished1 = 0, finished2 = 0;

void *t1(void *par)
{
    FILE *f = (FILE *)par;
    char *c;

    do
    {
        sem_wait(&sem_buff1w);
        fprintf(stdout, "Reading line\n");

        c = fgets(buff1, MAXLEN, f);

        if (c == NULL)
            buff1[0] = '\n';

        if (feof(f))
            finished1 = 1;

        fprintf(stdout, "Line read\n");
        sem_post(&sem_buff1r);
    } while (!feof(f));

    fprintf(stdout, "t1 exiting\n");
    pthread_exit(NULL);
}

void *t2(void *par)
{
    char buff[MAXLEN];
    int i, len;
    do
    {
        sem_wait(&sem_buff1r);
        fprintf(stdout, "Reading buffer\n");

        for (i = 0; buff1[i] != '\n'; i++)
            buff[i] = toupper(buff1[i]);

        buff[i] = '\0';

        fprintf(stdout, "Buffer read\n");

        len = i;

        sem_wait(&sem_buff2w);

        fprintf(stdout, "Writing upper\n");

        for (i = 0; i < len; i++)
            buff2[i] = buff[len - i - 1];

        buff2[i] = '\0';

        fprintf(stdout, "Uppers written\n");

        if (finished1)
            finished2 = 1;

        sem_post(&sem_buff1w);
        sem_post(&sem_buff2r);
    } while (!finished1);

    fprintf(stdout, "t2 exiting\n");
    pthread_exit(NULL);
}

void *t3(void *par)
{
    FILE *f = (FILE *)par;
    int n;

    do
    {
        sem_wait(&sem_buff2r);
        fprintf(stdout, "Writing result\n");

        n = fputs(buff2, f);
        if (n > 0)
            fprintf(f, "\n");

        fprintf(stdout, "Result written\n");
        sem_post(&sem_buff2w);
    } while (!finished2);

    fprintf(stdout, "t3 exiting\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int i;
    FILE *fin, *fout;
    pthread_t tid[3];
    if (argc == 3)
    {
        setbuf(stdout, 0);

        fin = fopen(argv[1], "r");
        fout = fopen(argv[2], "w");

        sem_init(&sem_buff1r, 0, 0);
        sem_init(&sem_buff1w, 0, 1);
        sem_init(&sem_buff2r, 0, 0);
        sem_init(&sem_buff2w, 0, 1);

        pthread_create(&tid[0], NULL, t1, (void *)fin);
        pthread_create(&tid[1], NULL, t2, NULL);
        pthread_create(&tid[2], NULL, t3, (void *)fout);

        for (i = 0; i < 3; i++)
            pthread_join(tid[i], NULL);

        sem_close(&sem_buff1r);
        sem_close(&sem_buff1w);
        sem_close(&sem_buff2r);
        sem_close(&sem_buff2w);

        fclose(fin);
        fclose(fout);
    }
    else
    {
        fprintf(stderr, "Usage: ./main infile outfile\n");
    }

    return 0;
}