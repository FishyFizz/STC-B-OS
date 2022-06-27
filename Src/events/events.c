#include "events.h"
#include "../button/button.h"
#include "../bit_ops/bit_ops.h"

XDATA u32 curr_events = 0;

XDATA u8 proc_waiting_evt = 0;
XDATA u32 proc_listening_list[8] = {0,0,0,0,0,0,0,0};
/*
    Example: process P waiting on event EVT_XXX and EVT_YYY
    proc_waiting_evt.bit[P] = 1;
    proc_listening_list[P] = EVT_XXX | EVT_YYY;
*/

void dispatch_events(u8 pid)
{
    if(proc_waiting_evt & BIT(pid))
    {
        if(proc_listening_list[pid] & curr_events)
        {
            /*
            process can read this to know which of 
            the listened events is actually occured.
            */
            proc_listening_list[pid] = curr_events; 
            CLEARBIT(proc_waiting_evt, pid);
        }
    }
}

void process_btnevts()
{
    update_button_state();

    if(btnstate_posedge & BTNSTATE_B1) curr_events |= EVT_BTN1_DN;
    if(btnstate_posedge & BTNSTATE_B2) curr_events |= EVT_BTN2_DN;
    if(btnstate_posedge & BTNSTATE_B3) curr_events |= EVT_BTN3_DN;
    if(btnstate_posedge & BTNSTATE_UP)      curr_events |= EVT_NAV_U;
    if(btnstate_posedge & BTNSTATE_DOWN)    curr_events |= EVT_NAV_D;
    if(btnstate_posedge & BTNSTATE_LEFT)    curr_events |= EVT_NAV_L;
    if(btnstate_posedge & BTNSTATE_RIGHT)   curr_events |= EVT_NAV_R;
    if(btnstate_posedge & BTNSTATE_PUSH)    curr_events |= EVT_NAV_PUSH;
    
    if(btnstate_negedge & BTNSTATE_B1) curr_events |= EVT_BTN1_UP;
    if(btnstate_negedge & BTNSTATE_B2) curr_events |= EVT_BTN2_UP;
    if(btnstate_negedge & BTNSTATE_B3) curr_events |= EVT_NAV_BTN3_RESET;
    if(btnstate_negedge & BTNSTATE_UP)      curr_events |= EVT_NAV_BTN3_RESET;
    if(btnstate_negedge & BTNSTATE_DOWN)    curr_events |= EVT_NAV_BTN3_RESET;
    if(btnstate_negedge & BTNSTATE_LEFT)    curr_events |= EVT_NAV_BTN3_RESET;
    if(btnstate_negedge & BTNSTATE_RIGHT)   curr_events |= EVT_NAV_BTN3_RESET;
    if(btnstate_negedge & BTNSTATE_PUSH)    curr_events |= EVT_NAV_BTN3_RESET;
}

void process_events()
{
    curr_events = 0;
    
    process_btnevts();

    dispatch_events(0);
    dispatch_events(1);
    dispatch_events(2);
    dispatch_events(3);
    dispatch_events(4);
    dispatch_events(5);
    dispatch_events(6);
    dispatch_events(7);
}