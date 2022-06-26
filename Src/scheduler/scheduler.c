#include "scheduler.h"
#include "../display/seg_led.h"
#include "../memcpy/memcpy.h"

XDATA u8 interrupt_frames[8][15];
XDATA u8 current_process = 0;
XDATA u32 system_cycles = 0;

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

    led_display_content = system_cycles>>4;
    DISP_LED();

    //=========================================================================
    //Load interrupt frame of current process
    my_memcpy((u8 IDATA*)(tmp_save_sp-16), interrupt_frames[current_process], 15);
}