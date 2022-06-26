#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_
#include "../global.h"

#define calc_TIM_from_ms_12t(t) ((u16)(65536 - (MAIN_Fosc / 12 / 1000 / 2 * t)))

void start_scheduler(u8 ms_per_interrupt);

#endif //_SCHEDULER_H_