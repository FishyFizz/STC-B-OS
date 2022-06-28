#include "global.h"
#include "scheduler/scheduler.h"
#include "display/seg_led.h"
#include "conc/semaphore.h"
#include "bit_ops/bit_ops.h"
#include "events/events.h"
#include "rs485/rs485.h"
#include "error/error.h"
#include "random/random.h"
#include "mem/mem.h"
#include "ds1302/ds1302.h"
#include "buzzer/buzzer.h"

void startup()
{
    seg_led_init();
    rs485_init(115200);
    LED_SEG_SWITCH = 1;

    LEDs = 0xFF;
    delay_ms(500);
    LEDs = 0x00;
    delay_ms(100);
    led_display_content = 0;
    seg_set_number(0);
	
	buzzer_init();
	buzzer_setfreq(660);
	buzzer_on();
	delay_ms(10);
	buzzer_off();
}

//RS485 TEST
/*
void proc1()
{
    XDATA u8 buf[4];
    XDATA u32 XDATA* ptr = (u32 XDATA*)buf;

    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_UART2_RECV);
        {
            if(MY_EVENTS & EVT_BTN1_DN)
            {
                *ptr = rand32();
                seg_set_number(*ptr);
                rs485_write(buf, 4);
            }
            else if(MY_EVENTS & EVT_UART2_RECV)
            {
                my_memcpy(buf, rs485_buf, 4);
                seg_set_number(*ptr);
            }
        }
    }
}
*/

//RTC TEST
/*
void proc1()
{
    ds1302_init();

    ds1302_writebyte(DS1302_WP,0x00);
    ds1302_writebyte(DS1302_SEC,0x00);
    sleep(100);
    while(1)
    {
        XDATA u8 sec = 0;
        NOINT_ATOMIC(
            ds1302_readbyte(sec, DS1302_SEC);
            seg_set_number((sec&0x0f) + 10*((sec&0x70)>>4));
        );
        sleep(100);
    }
}
*/


//Process sleep and yield test
void proc1()
{
	while(1)
	{
		seg_set_str("hello   ");
		sleep(1000);
		seg_set_str("world   ");
		sleep(1000);
	}
}

void proc2()
{
	while(1)
	{
		if(system_cycles > 5000)
			break;
		yield();
	}
	
	kill_process(1);
	
	while(1)
	{
		if(system_cycles > 10000)
			break;
		yield();
	}
	
	if(start_process(proc1)!=1)
		error_spin(55);
	
	while(1) yield();
}

XDATA u8 current = 0;
void main() //also proc0
{
    startup();

    start_scheduler(1);
    start_process(proc1);
	start_process(proc2);

    //DISPLAY DRIVER
    while(1)
	{   
		seg_led_scan_next();
		process_events();
        //LEDs = system_cycles>>3;
		led_display_content = proc_sleep_countdown[1];
		yield();
    }
}