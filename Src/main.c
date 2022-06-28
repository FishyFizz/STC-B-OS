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
#include "button/button.h"
#include "delay/delay.h"
#include "string_util/strfmt.h"

#include "test_process/test_process.h"

#define STARTUP_BLINK 
//#define STARTUP_BEEP

void startup();

void testproc()
{
    while(1)
    {
        wait_on_evts(EVT_BTN1_DN);
        {
			u32_to_str_hex(24561037);
			usbcom_write(fmtbuf+fmt_index,FMTBUF_LEN-1-fmt_index);
        }
    }
}

void main() //also proc0
{
    startup();
    start_scheduler(1);

	//start processes here.
	start_process(testproc, 0);
	
    //DISPLAY & EVENTS DRIVER
    while(1)
	{   
		seg_led_scan_next();
		process_events();
		yield();
    }
}

void startup()
{
    seg_led_init();
	led_display_content = 0;
    seg_set_number(0);

	buttons_init();
    rs485_init(115200);
	usbcom_init(115200);

#ifdef STARTUP_BLINK
	LED_SEG_SWITCH = USE_LED;
	LEDs = 0xAA;
	delay_ms(150);
	LEDs = 0x55;
	delay_ms(150);
	DISP_LED();
	delay_ms(150);
#endif

#ifdef STARTUP_BEEP
	buzzer_setfreq(440);
	buzzer_on();
	delay_ms(50);
	buzzer_off();
#endif
}
