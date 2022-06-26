#include "global.h"
#include "scheduler/scheduler.h"
#include "display/seg_led.h"

void startup()
{
    seg_led_init();
    led_display_content = 0xFF;
    DISP_LED();
    delay_ms(500);
    led_display_content = 0x00;
    DISP_LED();
    delay_ms(100);
}

void proc1()
{
    while(1)
    {
        led_display_content = 0x02;
        DISP_LED();
    }
}

void proc2()
{
    while(1)
    {
        led_display_content = 0x04;
        DISP_LED();
    }
}

void main() //also proc0
{
    startup();

    start_scheduler(1);
    start_process(proc1);
    start_process(proc2);

    while(1)
    {
        delay_ms(255);
        delay_ms(255);
        delay_ms(255);
        delay_ms(255);
        delay_ms(255);
        delay_ms(255);
        
        flag_nosched = 1;
        led_display_content = 0x01;
        DISP_LED();
    }
}