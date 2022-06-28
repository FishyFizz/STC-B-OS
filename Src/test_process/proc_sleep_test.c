#include "test_process.h"

void proc_sleep1()
{
	while(1)
	{
        seg_set_str("hello   ");
        sleep(2000);
	}
}

void proc_sleep2()
{
    sleep(1000);
    while(1)
    {
        seg_set_str("world   ");
        sleep(2000);
    }
}

void sleep_test()
{
    start_process(proc_sleep1, 0);
    start_process(proc_sleep2, 0);
    while(1){yield();}
}