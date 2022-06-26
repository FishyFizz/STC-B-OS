#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "../global.h"

#define calc_TIM_from_ms_12t(t) ((u16)(65536 - (MAIN_Fosc / 12 / 1000 / 2 * t)))
#define BIT(x) ((u8)(1<<(x)))

extern XDATA u8 interrupt_frames[8][15];
extern XDATA u8 current_process;
extern XDATA u32 system_cycles;
extern XDATA u8 process_slot;

typedef void (CODE *PROCESS_ENTRY)();

void start_scheduler(u8 ms_per_interrupt);
u8 select_process();
void start_process(PROCESS_ENTRY entry);
void error_spin(u8 errorcode);
u8 process_ready(u8 pid);

#endif //_SCHEDULER_H_