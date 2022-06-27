#ifndef _CLOCK_INT_H_
#define _CLOCK_INT_H_

#include "../global.h"

/*
Freq = MAIN_Fosc / (65536 - RL_T0) / 2
RL_T0 = 65536 - ( Main_Fosc / 2 / Freq )
*/

#define check_legal_ms_1t(t) ((MAIN_Fosc / 1000 / 2 * t) < 65000)
#define calc_TIM_from_ms_1t(t) ((u16)(65536 - (MAIN_Fosc / 1000 / 2 * t)))

#define check_legal_freq_1t(f) ((MAIN_Fosc / f / 2) < 65000)
#define calc_TIM_from_freq_1t(f) ((u16)(65536 - (MAIN_Fosc / f / 2)))

#define check_legal_ms_12t(t) ((MAIN_Fosc / 12 / 1000 / 2 * t) < 65000)
#define calc_TIM_from_ms_12t(t) ((u16)(65536 - (MAIN_Fosc / 12 / 1000 / 2 * t)))

#define check_legal_freq_12t(f) ((MAIN_Fosc / 12 / 2 / f) < 65000)
#define calc_TIM_from_freq_12t(f) ((u16)(65536 - (MAIN_Fosc / 12 / 2 / f)))

/*

IMPORTANT!!!!!!

    1.  Timer1 is reserved to Buzzer to generate tone frequency
        Timer2 is reserved to UART2 to generate baud rate frequency

    2.  When a timer is used to generate interrupts, 
        interrupts will occur on BOTH rising and falling edge!
        Interrupt rate = 2* [Timer or Clock rate].
*/


#endif //_CLOCK_INT_H_