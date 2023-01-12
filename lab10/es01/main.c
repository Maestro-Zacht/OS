#include <stdio.h>
#include <semaphore.h>

sem_t s_aorb, s_aorb_finished, s_nC, s_c_finished;
int nC;

void A_prol()
{
    sem_wait(&s_aorb);
}

void B_prol()
{
    A_prol();
}

void C_prol()
{
    sem_wait(&s_nC);
    if (nC == 0)
        sem_post(&s_c_finished);
    nC++;
    sem_post(&s_nC);
}

void D_prol()
{
    sem_wait(&s_c_finished);
}

void A_epil()
{
    sem_post(&s_aorb_finished);
}

void B_epil()
{
    A_epil();
}

void C_epil()
{
    sem_wait(&s_nC);
    nC--;
    if (nC == 0)
        sem_post(&s_aorb_finished);
    sem_post(&s_nC);
}

void D_epil()
{
    sem_post(&s_aorb);
}

int main()
{
    sem_init(&s_aorb, 0, 1);
    sem_init(&s_aorb_finished, 0, 0);
    sem_init(&s_nC, 0, 0);
    nC = 0;
    sem_init(&s_c_finished, 0, 0);

    return 0;
}