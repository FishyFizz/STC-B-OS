#include "scheduler.h"
#include "../display/seg_led.h"
#include "../memcpy/memcpy.h"

XDATA u8 interrupt_frames[8][15];
XDATA u8 current_process = 0;
XDATA u32 system_cycles = 0;
XDATA u8 process_slot = 1;

void start_scheduler(u8 ms_per_interrupt)
{
    //Set Timer0, Enable interrupt.
    {   
        XDATA TIM_InitTypeDef timer_settings;
        timer_settings.TIM_Mode = TIM_16BitAutoReload;
        timer_settings.TIM_Polity = PolityHigh;
        timer_settings.TIM_Interrupt = ENABLE;
        timer_settings.TIM_ClkSource = TIM_CLOCK_12T;
        timer_settings.TIM_ClkOut = DISABLE;
        timer_settings.TIM_Value = calc_TIM_from_ms_12t(ms_per_interrupt*2);
        timer_settings.TIM_Run = ENABLE;
        Timer_Inilize(Timer0, &timer_settings);
    }
}

DATA u8 tmp_save_sp;
void timer0_interrupt()
{
    //Save interrupt frame of current process
    tmp_save_sp = SP;
    my_memcpy(interrupt_frames[current_process], (u8 IDATA*)(tmp_save_sp-16), 15);
    //=========================================================================

    system_cycles++;
    current_process = select_process();
    if(current_process >= 8)    //can't find a process to run
        error_spin(1);           


    //Debug
    led_display_content = system_cycles>>4;
    DISP_LED();

    //=========================================================================
    //Load interrupt frame of current process
    my_memcpy((u8 IDATA*)(tmp_save_sp-16), interrupt_frames[current_process], 15);
}

XDATA u8 tmp_process;
u8 select_process()
{
    tmp_process = current_process;

    //sequentially check other processes
    while(++tmp_process != current_process)
        if(process_ready(tmp_process))
            return tmp_process;

    //if no other process can run, check if current process can run again
    if (process_ready(current_process))
        return current_process;
    
    //Can't find a process to run, Error code 1.
    error_spin(1);
}

u8 process_ready(u8 pid)
{
    //Check process exists
    if(!(process_slot & BIT(pid)))
        return 0;
    
    return 1;
}

void start_process(PROCESS_ENTRY entry)
{

}

XDATA u8 tmp_curr_seg;
void error_spin(u8 errorcode)
{
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