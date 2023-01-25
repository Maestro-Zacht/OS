#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int *V, start, end;
} param_t;

void merge(int *B, int start, int end)
{
    int i = start, j = (end + start) / 2, k = 0;
    int *A = (int *)malloc((end - start) * sizeof(int));

    while (i < (end + start) / 2 && j < end)
        A[k++] = (B[i] < B[j]) ? B[i++] : B[j++];

    while (i < (end + start) / 2)
        A[k++] = B[i++];

    while (j < end)
        A[k++] = B[j++];

    for (i = start, k = 0; i < end; i++, k++)
        B[i] = A[k];

    free(A);
}

void *mergeSort(void *par)
{
    param_t *data = (param_t *)par, par1, par2;
    pthread_t tid1, tid2;

    if (data->end - data->start == 1)
        pthread_exit(NULL);

    par1.start = data->start;
    par1.end = (data->end + data->start) / 2;
    par1.V = data->V;

    pthread_create(&tid1, NULL, mergeSort, (void *)(&par1));

    par2.start = par1.end;
    par2.end = data->end;
    par2.V = data->V;

    pthread_create(&tid2, NULL, mergeSort, (void *)(&par2));

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    merge(data->V, data->start, data->end);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int *V, N, i;
    pthread_t tid;
    param_t par;

    if (argc == 2)
    {
        N = atoi(argv[1]);

        srand(time(NULL));

        V = (int *)malloc(N * sizeof(int));

        for (i = 0; i < N; i++)
        {
            V[i] = rand();
            fprintf(stdout, "%d\n", V[i]);
        }

        par.V = V;
        par.start = 0;
        par.end = N;

        pthread_create(&tid, NULL, mergeSort, (void *)(&par));
        pthread_join(tid, NULL);

        fprintf(stdout, "\n\n");

        for (i = 0; i < N; i++)
            fprintf(stdout, "%d\n", V[i]);

        free(V);
    }

    return 0;
}