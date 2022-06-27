#include "global.h"
#include "scheduler/scheduler.h"
#include "display/seg_led.h"
#include "conc/semaphore.h"
#include "bit_ops/bit_ops.h"
#include "events/events.h"
#include "rs485/rs485.h"
#include "error/error.h"

void startup()
{
    seg_led_init();
    rs485_init(1200);
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
    XDATA u8 buf[8] = {0,0,0,0,0,0,0,0};
    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_UART2_RECV);
        {
            if(MY_EVENTS & EVT_BTN1_DN)
            {
                buf[0]++;
                seg_set_number(buf[0]);
                rs485_write(buf, 1);
            }
            else if(MY_EVENTS & EVT_UART2_RECV)
                led_display_content = rs485_buf[0];   
        }
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