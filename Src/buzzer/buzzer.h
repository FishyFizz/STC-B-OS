#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "../global.h"
#include "../clock_util/clock_util.h"

#define BUZZER P34

#define buzzer_on() {TR1 = 1;}
#define buzzer_off() {TR1 = 0;}

#define NOTE_C  0
#define NOTE_Cs 1
#define NOTE_D	2
#define NOTE_Ds 3
#define NOTE_E	4
#define NOTE_F  5
#define NOTE_Fs 6
#define NOTE_G  7
#define NOTE_Gs 8
#define NOTE_A  9
#define NOTE_As 10
#define NOTE_B  11

#define OCT_1 0
#define OCT_2 1
#define OCT_3 2
#define OCT_4 3
#define OCT_5 4
#define OCT_6 5

#define NOTEFREQ(note,oct) (freq_table[OCT_##oct - 1][NOTE_##note])

extern CODE u16 freq_table[5][12];

void buzzer_init();
void buzzer_setfreq(u16 freq);
#define buzzer_setnote(note,oct) {buzzer_setfreq(NOTEFREQ(note,oct));}

extern XDATA u16 __freq;
extern XDATA u16 __timebase;
extern XDATA u32 __time;
void __buzzer_play();
#define buzzer_play(note,oct,time) {__freq = NOTEFREQ(note,oct); __time = time*__timebase; __buzzer_play();}
#define buzzer_set_timebase(tb) {__timebase = tb;}
#define buzzer_rest(time) {sleep(time*__timebase);}
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