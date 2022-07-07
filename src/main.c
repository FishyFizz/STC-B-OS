#include "global.h"
#include "stack.h"
#include "xstack.h"
#include "scheduler.h"
#include "bit_ops.h"
#include "timer0_isr.h"
#include "syscall.h"
#include "semaphore.h"
#include "events.h"
#include "seg_led.h"
#include "button.h"
#include "usbcom.h"
#include "rs485.h"
#include "random.h"

#define TIMESLICE_MS	1
#define T12RL		(65536 - MAIN_Fosc*TIMESLICE_MS/12/1000) 


void testproc(u16 param) large reentrant
{
	while(1)
	{
		if((timer0_cnt>>5) & BIT(param))
		{
			SETBIT(led_display_content, param);
		}
		else
		{
			CLEARBIT(led_display_content, param);
		}
	}
}

void testproc2(u16 param) large reentrant
{
	while(1)
	{
		proc_sleep(param);
		led_display_content = ~led_display_content;
	}
}

void testproc3(u16 param) large reentrant
{
	while(1)
	{
		proc_sleep(param);
		led_display_content ^= 0x0f;
	}
}

void testproc4() large reentrant
{
	while(1)
	{
		proc_sleep(500);
		sem_post(0);
		led_display_content |= 0x80;
		sem_wait(0);
		led_display_content &= ~0x80;
	}
}

void testproc5() large reentrant
{
	sem_init(0,0);
	while(1)
	{
		sem_wait(0);
		led_display_content |= 0x40;
		proc_sleep(500);
		sem_post(0);
		led_display_content &= ~0x40;
	}
}

void testproc6(u16 param) large reentrant
{
	while(1)
	{
		proc_wait_evts(EVT_BTN1_DN);
		seg_set_str("HELLO   ");
		usbcom_write("hello \0",0);
		proc_wait_evts(EVT_NAV_R);
		seg_set_str("WORLD   ");
		usbcom_write("world\r\n\0",0);
		proc_wait_evts(EVT_UART1_RECV);
		seg_set_str(usbcom_buf);
	}
}

void testproc7(u16 param) large reentrant
{
	while(1)
	{
		proc_wait_evts(EVT_UART2_RECV | EVT_BTN1_DN);
		if(MY_EVENTS & EVT_BTN1_DN)
		{
			*((u32 *)rs485_buf) = rand32();
			rs485_write(rs485_buf, 4);
			seg_set_number(*((u32 *)rs485_buf));
		}
		else
		{
			seg_set_number(*((u32 *)rs485_buf));
		}
	}
}

main()
{
	//initialize kernel stack and xstack pointer
	SP = kernel_stack;
	setxbp(kernel_xstack + KERNEL_XSTACKSIZE);
	
	//set process stacks and swap stacks owner
	process_stack[0][PROCESS_STACKSIZE-1] = 0;
	process_stack[1][PROCESS_STACKSIZE-1] = 1;
	process_stack[2][PROCESS_STACKSIZE-1] = 2;
	process_stack[3][PROCESS_STACKSIZE-1] = 3;
	process_stack[4][PROCESS_STACKSIZE-1] = 4;
	process_stack_swap[0][PROCESS_STACKSIZE-1] = 5;
	process_stack_swap[1][PROCESS_STACKSIZE-1] = 6;
	process_stack_swap[2][PROCESS_STACKSIZE-1] = 7;
	
	//initialize LED pins
	P0M1 &= 0x00;
	P0M0 |= 0xff;
	P2M1 &= 0xf0;
	P2M0 |= 0x0f;
	//select LED, set all off
	P23 = 1;
	P0 = 0;

	//initialize buttons
	buttons_init();
	
	//initialize serial ports
	usbcom_init(115200);
	rs485_init(115200);
		
	//start process

		
		
	//initialize PCA2 interrupt (as syscall interrupt)
	//clear CCF2
	CCON &= ~0x04;
	//disable PCA2 module and set ECCF2
	CCAPM2 = 1;
	//low priority interrupt
	PPCA = 0;
	
	//start main timer
	TR0 = 0;														//stop timer
	TMOD &= 0xF0;												//timer mode, 16b autoreload
	AUXR &= 0x7F;												//12T mode
	TL0 = T12RL & 0xff;							//set reload value
	TH0 = (T12RL & 0xff00) >> 8;
	ET0 = EA = 1;												//set interrupt enable
	PT0 = 0;														//set priority to low
	TR0 = 1;														//start timer
	
	//spin
	while(1);
}