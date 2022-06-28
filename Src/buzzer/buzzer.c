#include "buzzer.h"
#include "../scheduler/scheduler.h"

CODE u16 freq_table[5][12] = {
	65, 69, 73, 77, 82, 87, 92, 97, 103, 110, 116, 123,
	130, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246,
	261, 277, 293, 311, 329, 349, 369, 391, 415, 440, 466, 493,
	523, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987,
	1046, 1108, 1174, 1244, 1318, 1396, 1479, 1567, 1661, 1760, 1864, 1975
};

void buzzer_init()
{
    //Set Buzzer pin (P34) to Push-Pull mode (M1 = 0, M0 = 1)
    P3M1 &= 0xEF; // 1110 1111
    P3M0 |= 0x10; // 0001 0000

    //Setup Timer1
    TR1 = 0;    //Stop Timer1
    ET1 = 0;    //Disable interrupt
    PT1 = 0;    
    TMOD = (TMOD & ~0x30) | TIM_16BitAutoReload;    //Set timer mode
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

XDATA u16 __freq;
XDATA u16 __timebase;
XDATA u32 __time;
void __buzzer_play()
{
	buzzer_setfreq(__freq);
	buzzer_on();
	sleep(__time);
	buzzer_off();
}