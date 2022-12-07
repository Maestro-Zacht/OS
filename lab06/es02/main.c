#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXSTR 1024

struct param
{
    int n;
    char name_in[MAXSTR];
    char name_out[MAXSTR];
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
    int n, i, *vet;
    struct param *data = (struct param *)arg;
    char fnin[MAXSTR], fnout[MAXSTR];
    FILE *f, *fout;

    sprintf(fnin, "%s%d.txt", data->name_in, data->n);
    sprintf(fnout, "%s%d.txt", data->name_out, data->n);

    f = fopen(fnin, "r");
    fout = fopen(fnout, "w");

    if (f == NULL || fout == NULL)
    {
        fprintf(stderr, "Error with files\n");
        exit(-1);
    }

    fscanf(f, "%d", &n);
    vet = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        fscanf(f, "%d", &vet[i]);

    bubblesort(vet, n);

    fprintf(fout, "%d\n", n);

    for (i = 0; i < n; i++)
        fprintf(fout, "%d\n", vet[i]);

    fclose(f);
    fclose(fout);
    free(vet);

    return NULL;
}

int main(int argc, char *argv[])
{
    int n, i;
    struct param *par;
    pthread_t *tids;

    if (argc == 4)
    {
        n = atoi(argv[1]);
        par = (struct param *)malloc(n * sizeof(struct param));
        tids = (pthread_t *)malloc(n * sizeof(pthread_t));

        for (i = 0; i < n; i++)
        {
            par[i].n = i + 1;
            strcpy(par[i].name_in, argv[2]);
            strcpy(par[i].name_out, argv[3]);

            pthread_create(&tids[i], NULL, ordina, (void *)(&par[i]));
        }

        for (i = 0; i < n; i++)
            pthread_join(tids[i], NULL);

        free(par);
        free(tids);
    }
    else
    {
        fprintf(stderr, "Usage: main <n> <strIn> <strOut>\n");
    }
    return 0;
}