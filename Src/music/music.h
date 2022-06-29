#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "../global.h"
#include "../buzzer/buzzer.h"

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
#define buzzer_setnote(note,oct) {buzzer_setfreq(NOTEFREQ(note,oct));}
#define buzzer_play(note,oct,time) {__freq = NOTEFREQ(note,oct); __time = time*__timebase; __buzzer_play();}
#define buzzer_set_timebase(tb) {__timebase = tb;}
#define buzzer_rest(time) {sleep(time*__timebase);}

extern XDATA u16 __freq;
extern XDATA u16 __timebase;
extern XDATA u32 __time;
void __buzzer_play();

extern CODE u16 freq_table[5][12];

/*
    music_msg structure:

    Basic Message
        MSB<-------------------------------------------------------------------->LSB
    [0]|         0        |  7bit note index starting from C1                    |
    [1]|    4bit rest length after the note    |      4bit  note length          |

    Pure Note/Pure Rest
        MSB<-------------------------------------------------------------------->LSB
    [0]|         1        |  3bit note octave  |  4bit note name (from C to B)   |
    [1]|  0=Note 1=Rest   |               7bit note or rest length               |

*/
#define NOTEINDEX(m) ((m)&0x7f)
#define PURELEN(m) (((m)&0x7f00)>>8)

#define _NOTELEN(m) (((m)&0xf00)>>8)
#define _RESTLEN(m) (((m)&0xf000)>>12)

#define _PURENOTE(m) (m&0x8000)
#define ISPURE(m)   (m&0x80)

#define NOTELEN(m) (ISPURE(m)? (_PURENOTE(m)?PURELEN(m):0) : _NOTELEN(m))
#define RESTLEN(m) (ISPURE(m)? (_PURENOTE(m)?0:PURELEN(m)) : _RESTLEN(m))

void play_music(u16* blob, u16 len);


#endif