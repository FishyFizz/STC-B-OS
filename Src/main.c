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
#include "usbcom/usbcom.h"

void startup()
{
    seg_led_init();
    rs485_init(115200);
	usbcom_init(115200);
    LED_SEG_SWITCH = 1;

    LEDs = 0xFF;
    delay_ms(500);
    LEDs = 0x00;
    delay_ms(100);
    led_display_content = 0;
    seg_set_number(0);
	
	
	buzzer_init();
	/*
	buzzer_setnote(A, 3);
	buzzer_on();
	*/
	
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

//USBCOM TEST
/*
void proc1()
{
    XDATA u8 buf[4];
    XDATA u32 XDATA* ptr = (u32 XDATA*)buf;

    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_UART1_RECV);
        {
            if(MY_EVENTS & EVT_BTN1_DN)
            {
                *ptr = rand32();
                seg_set_number(*ptr);
                usbcom_write(buf, 4);
            }
            else if(MY_EVENTS & EVT_UART1_RECV)
            {
                my_memcpy(buf, usbcom_buf, 4);
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
/*
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
*/

/*Process kill test
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
*/

//semaphore test
/*
void proc1()
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

void proc2()
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
*/

//Buzzer music test (doudizhu)
void proc1()
{
	buzzer_set_timebase(200);
	
	while(1)
	{
		wait_on_evts(EVT_BTN1_DN);
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_play(E, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 4, 3);
		buzzer_rest(1);
		
		buzzer_play(E, 4, 1);
		buzzer_rest(1);
		buzzer_play(E, 4, 1);
		buzzer_play(D, 4, 1);
		buzzer_play(E, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_play(E, 5, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 5, 1);
		buzzer_play(A, 4, 3);
		buzzer_rest(1);
		
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(E, 5, 1);
		buzzer_rest(1);
		buzzer_play(E, 5, 1);
		buzzer_play(G, 5, 1);
		buzzer_play(E, 5, 1);
		buzzer_rest(1);
		
		buzzer_play(D, 5, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_rest(1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 4, 1);
		buzzer_rest(1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(G, 4, 3);
		buzzer_rest(1);

	}
}

//Buzzer music test (monster hunter)
void proc2()
{
	buzzer_set_timebase(80);
	while(1)
	{
		wait_on_evts(EVT_BTN1_DN);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_rest(2);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 6);
		buzzer_rest(2);
		buzzer_play(F, 5, 1);
		buzzer_rest(1);
		buzzer_play(Ds, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_play(As, 4, 4);
		buzzer_rest(2);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(Ds, 5, 2);
		buzzer_rest(2);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_play(As, 4, 4);
		buzzer_rest(2);
		buzzer_play(G, 4, 12);
		buzzer_rest(12);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_rest(2);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		
		buzzer_play(C, 6, 6);
		buzzer_rest(2);
		buzzer_play(As, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 6);
		buzzer_rest(6);
		
		buzzer_play(F, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 2);
		buzzer_rest(2);
		buzzer_play(G, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 1);
		buzzer_rest(1);
		buzzer_play(As, 5, 4);
		buzzer_rest(2);
		buzzer_play(D, 6, 4);
		buzzer_rest(2);
		buzzer_play(C, 6, 18);
		buzzer_rest(2);

	}
}

XDATA u8 current = 0;
void main() //also proc0
{
    startup();

    start_scheduler(1);
    start_process(proc2);
	//start_process(proc2);

    //DISPLAY DRIVER
    while(1)
	{   
		seg_led_scan_next();
		process_events();
        //LEDs = system_cycles>>3;
		yield();
    }
}