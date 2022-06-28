#include "test_process.h"

void killtest_proc1()
{
    while(1)
    {
        seg_set_str("hello   ");
    }
}

void killtest_proc2()
{
    while(1)
    {
        seg_set_str("world   ");
    }
}

XDATA u8 killtest_pid1;
XDATA u8 killtest_pid2;
XDATA u8 loop;
void kill_test()
{
    for(loop = 0; loop<3; loop++)
    {
        start_process(killtest_proc1, &killtest_pid1);
        sleep(1000);
        kill_process(killtest_pid1);

        start_process(killtest_proc2, &killtest_pid2);
        sleep(1000);
        kill_process(killtest_pid2);
    }

    kill_process(current_process);

    error_spin(5);
}