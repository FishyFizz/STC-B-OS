#include "buzzer.h"
#include "../scheduler/scheduler.h"


void buzzer_init()
{
    //Set Buzzer pin (P34) to Push-Pull mode (M1 = 0, M0 = 1)
    P3M1 &= 0xEF; // 1110 1111
    P3M0 |= 0x10; // 0001 0000

    //Setup Timer1
    TR1 = 0;    //Stop Timer1
    ET1 = 0;    //Disable interrupt
    PT1 = 0;    
    TMOD = (TMOD & ~0x30) | 0;    //Set timer mode - 16bit autoreload
    INT_CLKO |=  0x02; //Set timer output to P34
}

void buzzer_setfreq(u16 freq)
{
    if(check_legal_freq_1t(freq))
    {
        AUXR |=  0x40;	//1T
        TH1 = (u8) (calc_TIM_from_freq_1t(freq) >> 8);
				TL1 = (u8) calc_TIM_from_freq_1t(freq);
    }
    else if(check_legal_freq_12t(freq))
    {
        AUXR &= ~0x40; //12T
        TH1 = (u8) (calc_TIM_from_freq_12t(freq) >> 8);
				TL1 = (u8) calc_TIM_from_freq_12t(freq);
    }
}
