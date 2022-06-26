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
}

void proc1()
{
    while(1)
    {
        //blink led6
        sleep(2047);
        LEDs |= 0x40;

        sleep(2047);
        LEDs &= 0xBF;
    }
}

void proc2()
{
    while(1)
    {
        //spin
        yield();
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
        //blink led7
        sleep(1023);
        LEDs |= 0x80;

        sleep(1023);
        LEDs &= 0x7F;
    }
}