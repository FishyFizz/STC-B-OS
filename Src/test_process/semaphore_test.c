#include "test_process.h"

void sem_proc1()
{
    while(1)
    {
        sem_wait(0);
        SETBIT(led_display_content,6);
        sleep(2000);
        sem_post(0);
        CLEARBIT(led_display_content,6);
    }
}

void sem_proc2()
{
    while(1)
    {
        sleep(2000);
        SETBIT(led_display_content,7);
        sem_post(0);
        sem_wait(0);
        CLEARBIT(led_display_content, 7);
    }
}

void semaphore_test()
{
    sem_init(0,0);
    start_process(sem_proc1, 0);
    start_process(sem_proc2, 0);
    while(1){yield();}
}