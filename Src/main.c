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

void main()
{
    startup();

    EA = 1;
    start_scheduler(1);

    while(1);
}