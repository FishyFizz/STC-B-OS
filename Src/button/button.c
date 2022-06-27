#include "button.h"
#include "../adc/adsensor.h"

XDATA u8 __nav_btn3_state = 0xff;

XDATA u8 last2_btn_state    =0;
XDATA u8 last_btn_state     =0;
XDATA u8 curr_btn_state     =0;
XDATA u8 btnstate_posedge   =0;
XDATA u8 btnstate_negedge   =0;

void buttons_init()
{
    //Initialize ADC for Nav and Button3
    adc_init();

    //Set Button1 and Button2 pin to Weak Pullup (M1 = 0, M0 = 0)
    P3M1 &= 0xF3;   // 1111 0011
    P3M0 &= 0xF3;   // 1111 0011

    //Set P17 to Weak Pullup (M1 = 0, M0 = 0)
    //P17 Pullup -> Key3 -> Nav Button(different resistance) -> GND
    P1M1 &= 0x7F; // 0111 1111
    P1M0 &= 0x7F; // 0111 1111
}

void update_button_state()
{
    last2_btn_state = last_btn_state;
    last_btn_state = curr_btn_state;
    curr_btn_state = 0;

    update_nav_btn3_state();

    curr_btn_state |= BUTTON1       ?BTNSTATE_B1    :0;
    curr_btn_state |= BUTTON2       ?BTNSTATE_B2    :0;

    curr_btn_state |= IS_BTN3_PUSH  ?BTNSTATE_B3    :0;

    curr_btn_state |= IS_NAV_LEFT   ?BTNSTATE_LEFT  :0;
    curr_btn_state |= IS_NAV_RIGHT  ?BTNSTATE_RIGHT :0;
    curr_btn_state |= IS_NAV_UP     ?BTNSTATE_UP    :0;
    curr_btn_state |= IS_NAV_DOWN   ?BTNSTATE_DOWN  :0;
    curr_btn_state |= IS_BTN3_PUSH  ?BTNSTATE_PUSH  :0;

    // 2 recent samples must be same (buttons stabilized)
    if(curr_btn_state != last_btn_state)
    {
        btnstate_negedge = btnstate_posedge = 0;
        return;
    }

    //different with previous detection, and currently set -> posedge
    btnstate_posedge = (curr_btn_state ^ last2_btn_state) & (curr_btn_state);   

    //different with previous detection, and previously set -> negedge
    btnstate_negedge = (curr_btn_state ^ last2_btn_state) & (last2_btn_state);
}