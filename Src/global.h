#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "stc/config.h"
#include "stc/timer.h"
#include "stc/delay.h"

//#define STC

#ifndef STC
    #define XDATA
    #define IDATA
    #define DATA
    #define CODE
    #define INTERRUPT
#else
    #define XDATA       xdata
    #define IDATA       idata
    #define DATA        data
    #define CODE        code
    #define INTERRUPT   interrupt
#endif

#define BIT(x) ((u8)(1<<(x)))
#define CLEARBIT(var, bit) {(var) &= ~(1<<(bit));}
#define SETBIT(var, bit) {(var) |= (1<<(bit));}

extern XDATA u32 conc_test;

#endif //_GLOBAL_H_