#include "error.h"
#include "../display/seg_led.h"
#include "../mem/mem.h"

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

void message_spin(u8 errorcode)
{
    XDATA u16 spin = 100;
    
    XDATA u8  prev_seg_content[8];
    my_memcpy(prev_seg_content, seg_display_content,8);

    //disable timer0
    TR0 = 0;

    seg_set_str("MSG     ");

    seg_display_content[7]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[6]=seg_decoder[errorcode%10];
    errorcode/=10;
    seg_display_content[5]=seg_decoder[errorcode%10];
    errorcode/=10;

    while (--spin)
    {
        tmp_curr_seg++;
        DISP_SEG(tmp_curr_seg & 0x7);
        delay_ms(2);
    }
    
    my_memcpy(seg_display_content , prev_seg_content,8);
    
    //enable timer0
    TR0 = 1;
}