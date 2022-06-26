#include "semaphore.h"

XDATA char semaphores[MAX_SEMAPHORES];
XDATA u8 proc_sem_wait_flag[MAX_SEMAPHORES];
XDATA u8 sem_wake_round[MAX_SEMAPHORES];
XDATA u8 proc_waiting = 0;

void sem_init(u8 sem_id, char val)
{
    if (sem_id >= MAX_SEMAPHORES)
        error_spin(20);

    ATOMIC(
        proc_sem_wait_flag[sem_id] = 0;
        sem_wake_round[sem_id] = 1;
        semaphores[sem_id] = val;
    )
}

XDATA u8 select_wake;
void sem_post(u8 sem_id)
{
    ATOMIC_START();

    //No process is waiting, only increment semaphore
    if(!proc_sem_wait_flag[sem_id])
    {
        semaphores[sem_id]++;
        goto SEM_POST_END;
    }

    //Find first process waiting on the semaphore
    select_wake = RSL(sem_wake_round[sem_id]);
    while ((select_wake & proc_sem_wait_flag[sem_id]) == 0)
        select_wake = RSL(select_wake);

    //Remove the waiting flag of the process
    proc_sem_wait_flag[sem_id] &= ~select_wake;
    proc_waiting &= ~select_wake;

    //Record the last waked process
    sem_wake_round[sem_id] = select_wake;

    SEM_POST_END:;
    ATOMIC_END();
}

void sem_wait(u8 sem_id)
{
    ATOMIC_START();

    //semaphore currently idle, decrement value and return.
    if(semaphores[sem_id])
    {
        semaphores[sem_id] --;
        goto SEM_WAIT_END;
    }

    /*  
        set current process waiting on semaphore, yield
        (and the process won't be selected by scheduler 
        until wait flag is cleared by some sem_post)
    */

    proc_sem_wait_flag[sem_id] |= BIT(current_process);
    proc_waiting |= BIT(current_process);
    yield();

    SEM_WAIT_END:;
    ATOMIC_END();
}
