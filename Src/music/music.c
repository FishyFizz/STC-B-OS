#include "music.h"
#include "../scheduler/scheduler.h"
#include "../display/seg_led.h"

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

CODE u16 freq_table[5][12] = {
	65, 69, 73, 77, 82, 87, 92, 97, 103, 110, 116, 123,
	130, 138, 146, 155, 164, 174, 184, 195, 207, 220, 233, 246,
	261, 277, 293, 311, 329, 349, 369, 391, 415, 440, 466, 493,
	523, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987,
	1046, 1108, 1174, 1244, 1318, 1396, 1479, 1567, 1661, 1760, 1864, 1975
};

void play_music(u16* blob, u16 len)
{
    XDATA u16 i;
    XDATA u8 tmp_len;
    XDATA u16 tmp_msg;

    for(i=0;i<len;i++)
    {
        tmp_msg = blob[i];
        tmp_len = NOTELEN(tmp_msg);
        if(tmp_len)
        {
            buzzer_setfreq(freq_table[0][NOTEINDEX(tmp_msg)]);
            led_display_content = NOTEINDEX(tmp_msg);
            buzzer_on();
            sleep(__timebase*tmp_len);
            buzzer_off();
        }
        tmp_len = RESTLEN(tmp_msg);
        if(tmp_len)
        {
            sleep(__timebase*tmp_len);
        }
    }
}
