

struct lock
{
    int ticketNumber, turnNumber;
};

int atomicIncrement(int *var)
{
    int tmp = *var;
    *var = tmp + 1;
    return (tmp);
}

void init_lock(struct lock *l)
{
    l->ticketNumber = 0;
    l->turnNumber = 0;
}

void lock_lock(struct lock *l)
{
    int t = atomicIncrement(&l->ticketNumber);
    while (t != l->turnNumber)
        ;
}

void unlock_lock(struct lock *l)
{
    atomicIncrement(l->turnNumber);
}