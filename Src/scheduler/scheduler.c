#include "scheduler.h"
#include "../display/seg_led.h"

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

void timer0_interrupt()
{
    led_display_content++;
    DISP_LED();
}