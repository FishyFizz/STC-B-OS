#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "../global.h"

//BUTTON EVENTS================================
#define EVT_BTN1_DN     0x1
#define EVT_BTN1_UP     0x2

#define EVT_BTN2_DN     0x4
#define EVT_BTN2_UP     0x8

#define EVT_BTN3_DN     0x10
#define EVT_NAV_L       0x20    
#define EVT_NAV_R       0x40
#define EVT_NAV_U       0x80
#define EVT_NAV_D       0x100
#define EVT_NAV_PUSH    0x200

#define EVT_NAV_BTN3_RESET  0x400

//UART EVENTS==================================
#define EVT_UART1_RECV  0x800
#define EVT_UART2_RECV  0x1000

extern XDATA u32 curr_events;

extern XDATA u8 proc_waiting_evt;
extern XDATA u32 proc_listening_list[8];
#define MY_EVENTS (proc_listening_list[current_process])

void process_events();
void dispatch_events(u8);
void collect_btnevts();
void collect_uartevts();

#define wait_on_evts(evts)\
ATOMIC(\
    SETBIT(proc_waiting_evt, current_process);\
    proc_listening_list[current_process]=evts;\
    __yield();\
)

#endif //_EVENTS_H_