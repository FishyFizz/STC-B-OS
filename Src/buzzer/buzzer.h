#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "../global.h"
#include "../clock_util/clock_util.h"

#define BUZZER P34

#define buzzer_on() {TR1 = 1;}
#define buzzer_off() {TR1 = 0;}


void buzzer_init();
void buzzer_setfreq(u16 freq);

//NOTE: this "function" must be called in a process.



/*
    Usage:

    buzzer_init();
    buzzer_setfreq(440);
    buzzer_on();
    ...some delay...
    buzzer_off();
    
*/
#endif