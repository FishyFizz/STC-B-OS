#include "global.h"
#include "scheduler/scheduler.h"
#include "display/seg_led.h"

void startup()
{
    seg_led_init();
    LED_SEG_SWITCH = 1;

    LEDs = 0xFF;
    delay_ms(500);
    LEDs = 0x00;
    delay_ms(100);
    led_display_content = 0;
    seg_set_number(0);
}

XDATA u32 conc_test = 0;
void proc1()
{
    while(1)
    {
        sleep(100);
        SETBIT(led_display_content, 0);

        sleep(100);
        CLEARBIT(led_display_content, 0);
    }
}

void proc2()
{
    while(1)
    {
        sleep(200);
        SETBIT(led_display_content, 1);

        sleep(200);
        CLEARBIT(led_display_content, 1);
    }
}

void proc3()
{
    while(1)
    {
        sleep(400);
        SETBIT(led_display_content, 2);

        sleep(400);
        CLEARBIT(led_display_content, 2);
    }
}

void proc4()
{
    while(1)
    {
        sleep(800);
        SETBIT(led_display_content, 3);

        sleep(800);
        CLEARBIT(led_display_content, 3);
    }
}

void proc5()
{
    u16 inc_count = 0;
    for(inc_count = 0; inc_count < 5000; inc_count++){
        /*
        conc_test in XDATA, reading, increment in register, write back
        takes many CPU cycles to complete. During this time, a reschedule
        can happen, leading to a result smaller than expected.
        */
        ATOMIC(conc_test++;)
        //conc_test++;
    }

    while(1) yield();
}

void proc6()
{
    u16 inc_count = 0;
    for(inc_count = 0; inc_count < 5000; inc_count++){
        ATOMIC(conc_test++;)
        //conc_test++;
    }
    while(1) yield();
}

void proc7()
{
    u16 inc_count = 0;
    for(inc_count = 0; inc_count < 5000; inc_count++){
        ATOMIC(conc_test++;)
        //conc_test++;
    }
    while(1) yield();
}

XDATA u8 current = 0;
void main() //also proc0
{
    startup();

    start_scheduler(1);
    start_process(proc1);
    start_process(proc2);
    start_process(proc3);
    start_process(proc4);
    start_process(proc5);
    start_process(proc6);
    start_process(proc7);


    //DISPLAY DRIVER
    while(1)
    {
        seg_set_number(conc_test);
        switch(current)
        {
            case 0: DISP_SEG(0)     current++; break;
            case 1: DISP_SEG(1)     current++; break;
            case 2: DISP_SEG(2)     current++; break;
            case 3: DISP_SEG(3)     current++; break;
            case 4: DISP_SEG(4)     current++; break;
            case 5: DISP_SEG(5)     current++; break;
            case 6: DISP_SEG(6)     current++; break;
            case 7: DISP_SEG(7)     current++; break;
            case 8: DISP_LED()      current=0; break;
        }
        yield(); 
    }
}