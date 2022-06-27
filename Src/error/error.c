#include "error.h"
#include "../display/seg_led.h"

/*
    ERRCODES:

    1:  Scheduler can't find a process to run.
    2:  Process slots full, can't create more.
    10-17:  Process 0-7 should not be sleeping, but has a sleep countdown.
            You have to edit sleep_check according to your process' behaviours.
    20: Semaphore out of bound.
*/
XDATA u8 tmp_curr_seg;
void error_spin(u8 errorcode)
{
    //disable interrupts (spin forever)
    TR0 = 0;

    seg_set_str("ERROR   ");

    seg_display_content[7]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[6]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[5]=seg_decoder[errorcode%10];
    errorcode/=10;

    while (1)
    {
        tmp_curr_seg++;
        DISP_SEG(tmp_curr_seg & 0x7);
        delay_ms(2);
    }
}