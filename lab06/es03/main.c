#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAXSTR 1024

struct param
{
    int index, len;
    char name_in[MAXSTR];
};

int **data_matrix;

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

    sprintf(fnin, "%s%d.txt", data->name_in, data->index + 1);

    f = fopen(fnin, "r");

    if (f == NULL)
    {
        fprintf(stderr, "Error with files\ni: %d\nfile: %s\n", data->index, data->name_in);
        exit(-1);
    }

    for (i = 0; i < data->len; i++)
        fscanf(f, "%d", &data_matrix[data->index][i]);

    bubblesort(data_matrix[data->index], data->len);

    fclose(f);

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
    int n_files, i, len, *res, *vtmp;
    struct param *par;
    pthread_t *tids;

    if (argc == 5)
    {
        n_files = atoi(argv[1]);
        len = atoi(argv[4]);
        par = (struct param *)malloc(n_files * sizeof(struct param));
        tids = (pthread_t *)malloc(n_files * sizeof(pthread_t));
        res = (int *)malloc(n_files * len * sizeof(int));
        vtmp = (int *)malloc(n_files * len * sizeof(int));

        data_matrix = (int **)malloc(n_files * sizeof(int *));
        for (i = 0; i < n_files; i++)
            data_matrix[i] = (int *)malloc(len * sizeof(int));

        for (i = 0; i < n_files; i++)
        {
            par[i].index = i;
            strcpy(par[i].name_in, argv[2]);
            par[i].len = len;

            pthread_create(&tids[i], NULL, ordina, (void *)(&par[i]));
        }

        for (i = 0; i < n_files; i++)
        {
            pthread_join(tids[i], NULL);
            memcpy(vtmp, res, i * len * sizeof(int));
            merge(res, vtmp, data_matrix[i], i * len, len);
        }

        fprintf(stdout, "\n");

        for (i = 0; i < n_files * len; i++)
            fprintf(stdout, "%d\n", res[i]);

        free(par);
        free(tids);
        for (i = 0; i < n_files; i++)
            free(data_matrix[i]);
        free(data_matrix);
        free(res);
        free(vtmp);
    }
    else
    {
        fprintf(stderr, "Usage: main <n> <strIn> <strOut> <len>\n");
    }
    return 0;
}