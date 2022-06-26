#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "../global.h"

#define DEFAULT_TIMESLICES 20

#define INTFRM_ADDRLO 0
#define INTFRM_ADDRHI 1

#define calc_TIM_from_ms_12t(t) ((u16)(65536 - (MAIN_Fosc / 12 / 1000 / 2 * t)))
#define BIT(x) ((u8)(1<<(x)))
#define NEXT(x) (((x)+1) & 0x7)
#define PROC_EXISTS(x) ((process_slot & BIT(x))>0)

extern XDATA u8 interrupt_frames[8][15];
extern XDATA u8 current_process;
extern XDATA u32 system_cycles;
extern XDATA u8 process_slot;

extern XDATA u8 remaining_timeslices;
extern XDATA u8 proc_time_share[8];

/*
This variable MUST be in DATA memory, because write or read to this
variable must be done atomically (single instruction), otherwise
rescheduel may happen during data access.

When set to 1, no rescheduling is performed in ISR, but system time
counter is incremented.
*/
extern DATA u8 flag_nosched;
#define ATOMIC_START() {flag_nosched = 1;}
#define ATOMIC_END() {flag_nosched = 0;}
#define ATOMIC(atomic_code)\
    flag_nosched = 1;\
    atomic_code\
    flag_nosched = 0;

typedef void (CODE *PROCESS_ENTRY)();

void start_scheduler(u8 ms_per_interrupt);

u8 select_process();

u8 __start_process(PROCESS_ENTRY entry);
#define start_process(entry) {flag_nosched = 1; __start_process(entry); flag_nosched=0;}

void error_spin(u8 errorcode);
u8 process_ready(u8 pid);
u8 find_empty_slot();

#endif //_SCHEDULER_H_