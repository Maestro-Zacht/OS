#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXSTR 1024
#define MAXLEN 1024
#define MAXNFILES 512

struct param
{
    int n, len, vet[MAXLEN];
    char name_in[MAXSTR];
};

void bubblesort(int *v, int n)
{
    int i, j, val;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (v[j] > v[j + 1])
            {
                val = v[j];
                v[j] = v[j + 1];
                v[j + 1] = val;
            }
        }
    }
}

void *ordina(void *arg)
{
    int i;
    struct param *data = (struct param *)arg;
    char fnin[MAXSTR];
    FILE *f;

    sprintf(fnin, "%s%d.txt", data->name_in, data->n);

    f = fopen(fnin, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error with files\nn: %d\nfile: %s\n", data->n, data->name_in);
        exit(-1);
    }

    for (i = 0; i < data->len; i++)
        fscanf(f, "%d", &data->vet[i]);

    fclose(f);

    bubblesort(data->vet, data->len);

    return NULL;
}

void merge(int *dest, int *source1, int *source2, int n1, int n2)
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
        dest[k++] = (source1[i] < source2[j]) ? source1[i++] : source2[j++];

    while (i < n1)
        dest[k++] = source1[i++];

    while (j < n2)
        dest[k++] = source2[j++];
}

int main(int argc, char *argv[])
{
    int n_files, i, len, res[MAXNFILES * MAXLEN], vtmp[MAXNFILES * MAXLEN];
    struct param par[MAXNFILES];
    pthread_t tids[MAXNFILES];

    if (argc == 5)
    {
        n_files = atoi(argv[1]);
        len = atoi(argv[4]);

        for (i = 0; i < n_files; i++)
        {
            par[i].n = i + 1;
            strcpy(par[i].name_in, argv[2]);
            par[i].len = len;

            pthread_create(&tids[i], NULL, ordina, (void *)(&par[i]));
        }

        for (i = 0; i < n_files; i++)
        {
            pthread_join(tids[i], NULL);
            memcpy(vtmp, res, i * len * sizeof(int));
            merge(res, vtmp, par[i].vet, i * len, len);
        }

        fprintf(stdout, "\n");

        for (i = 0; i < n_files * len; i++)
            fprintf(stdout, "%d\n", res[i]);
    }
    else
    {
        fprintf(stderr, "Usage: main <n> <strIn> <strOut> <len>\n");
    }
    return 0;
}