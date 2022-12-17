#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

#define OFFSETBASE (sizeof(float) * 2 + sizeof(int))

typedef struct
{
    int file, index;
    pthread_mutex_t *file_mutex;
} param_t;

int finished[3] = {0};
float monomio[3];
sem_t semt[3], semcalc;

float power(float x, int n)
{
    int i;
    float r = 1;

    for (i = 0; i < n; i++)
        r *= x;

    return r;
}

void *reader(void *par)
{
    param_t *data = (param_t *)par;
    int i = 0, n, ret;
    float c, x, r;

    while (!finished[data->index])
    {

        pthread_mutex_lock(data->file_mutex);

        lseek(data->file, i * OFFSETBASE * 3 + OFFSETBASE * data->index, SEEK_SET);

        ret = read(data->file, &c, sizeof(float));
        read(data->file, &x, sizeof(float));
        read(data->file, &n, sizeof(int));

        pthread_mutex_unlock(data->file_mutex);

        sem_wait(&semt[data->index]);
        if (ret == 0)
        {
            finished[data->index] = 1;
            r = 0;
        }
        else
        {
            r = c * power(x, n);
            i++;
        }

        monomio[data->index] = r;
        sem_post(&semcalc);
    }

    pthread_exit(NULL);
}

void *printer(void *par)
{
    int i, count = 1, cont;
    float sum;
    do
    {
        for (i = 0; i < 3; i++)
            sem_wait(&semcalc);

        sum = monomio[0] + monomio[1] + monomio[2];

        if (!finished[0] || !finished[1] || !finished[2])
            fprintf(stdout, "Monomio %d: %f\n", count++, sum);

        cont = finished[0] + finished[1] + finished[2];

        for (i = 0; i < 3; i++)
            sem_post(&semt[i]);
    } while (cont == 0);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int file, i;
    param_t params[3];
    pthread_mutex_t mutex;
    pthread_t tids[4];

    if (argc == 2)
    {
        setbuf(stdout, 0);
        file = open(argv[1], O_RDONLY);
        pthread_mutex_init(&mutex, NULL);

        sem_init(&semcalc, 0, 0);

        for (i = 0; i < 3; i++)
        {
            params[i].file = file;
            params[i].file_mutex = &mutex;
            params[i].index = i;

            sem_init(&semt[i], 0, 1);

            pthread_create(&tids[i], NULL, reader, &params[i]);
        }

        pthread_create(&tids[3], NULL, printer, NULL);

        for (i = 0; i < 4; i++)
            pthread_join(tids[i], NULL);

        close(file);
        pthread_mutex_destroy(&mutex);
        sem_destroy(&semcalc);
        for (i = 0; i < 3; i++)
            sem_destroy(&semt[i]);
    }

    return 0;
}