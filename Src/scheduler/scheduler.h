#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "../global.h"
#include "contextswitch.h"

#define DEFAULT_TIMESLICES 3

#define INTFRM_ADDRLO 0
#define INTFRM_ADDRHI 1
#define INTFRM_STACKPTR 15

#define NEXT(x) (((x)+1) & 0x7)
#define PROC_EXISTS(x) ((process_slot & BIT(x))>0)

extern XDATA u8 current_process;
extern XDATA u32 system_cycles;
extern XDATA u8 process_slot;

extern XDATA u8 remaining_timeslices;
extern XDATA u8 proc_time_share[8];

#define COUNTDOWN(from, cnt) {if((from)>=(cnt)) (from)-=(cnt); else (from)=0;}
extern XDATA u16 proc_sleep_countdown[8];

/*
This variable MUST be in DATA memory, because write or read to this
variable must be done atomically (single instruction), otherwise
rescheduel may happen during data access.

When set to 1, no rescheduling is performed in ISR, but system time
counter is incremented.
*/
extern DATA u8 flag_nosched;
extern DATA u8 interrupt_counter;
#define ATOMIC_START() {flag_nosched = 1;}
#define ATOMIC_END() {flag_nosched = 0;}
#define ATOMIC(atomic_code)\
{\
    flag_nosched = 1;\
    {atomic_code;}\
    flag_nosched = 0;\
}

#define NOINT_ATOMIC_START(){TR0 = 0;}
#define NOINT_ATOMIC_END(){TR0 = 1;}
#define NOINT_ATOMIC(atomic_code)\
{\
    TR0 = 0;\
    {atomic_code;}\
    TR0 = 1;\
}


typedef void (CODE *PROCESS_ENTRY)();

void __start_scheduler(u8 ms_per_interrupt);
#define start_scheduler(ms_per_interrupt) {__start_scheduler(ms_per_interrupt); SP = __stack;TR0 = 1;}

u8 select_process();

void __start_process(PROCESS_ENTRY entry,u8* ppid);
#define start_process(entry,ppid) ATOMIC(__start_process(entry,ppid););

void error_spin(u8 errorcode);
u8 process_ready(u8 pid);
u8 find_empty_slot();
u8 find_runnable();


void decrement_sleep_counters();

/*
implementation of yield, switch to another process right away.
Current processes state is needed to find the appropriate process
to switch to, so it can't be changed. Lock is needed when calling yield.
*/
void __reschedule();
extern void __yield();  //ASM code entrance
#define yield() {__yield();}
#define sleep(time) {\
    ATOMIC(\
        proc_sleep_countdown[current_process] = (time);\
        sleep_check();\
        __yield();\
    )\
}

void sleep_check();

void kill_process(u8 pid);

/*
IMPORTANT NOTE:

Due to CPU architecture problem (no multiple stacks), process must be 
at their root routine (not inside any function call) when getting 
rescheduled. So function calls must be atomic.

*/

#endif //_SCHEDULER_H_