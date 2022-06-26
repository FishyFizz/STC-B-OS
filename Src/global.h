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

#endif //_GLOBAL_H_