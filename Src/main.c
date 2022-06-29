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
#include "music/music.h"

#include "test_process/test_process.h"

#define STARTUP_BLINK 
//#define STARTUP_BEEP

void startup();


CODE u16 music[]={
	0x118, 0x11a, 0x111c, 0x118, 0x1215, 0x111a, 0x1117, 0x113, 0x1210, 0x1117, 0x1115, 0x113, 0x120c, 0x1113, 0x2410, 0x10e,
	0x110, 0x2211, 0x1118, 0x117, 0x118, 0x2213, 0x1111, 0x110, 0x111, 0x2212, 0x1118, 0x117, 0x115, 0x2414
};

void testproc()
{
	wait_on_evts(EVT_BTN1_DN);
	buzzer_set_timebase(170);
	play_music(music, 30);
	while(1) yield();
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
    rs485_init(460800);
	usbcom_init(460800);
	buzzer_init();
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
