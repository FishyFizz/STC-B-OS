#include "global.h"
#include "scheduler/scheduler.h"
#include "display/seg_led.h"
#include "conc/semaphore.h"
#include "bit_ops/bit_ops.h"
#include "events/events.h"

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

void proc1()
{
    XDATA u8 count = 0;
    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_BTN1_UP);
        seg_set_number(++count);
    }
}

XDATA u8 current = 0;
void main() //also proc0
{
    startup();

    start_scheduler(1);
    start_process(proc1);

    //DISPLAY DRIVER
    while(1)
    {   
        ATOMIC(
            seg_led_scan_next();
            process_events();
        )
        yield(); 
    }
}