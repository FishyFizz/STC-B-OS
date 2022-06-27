#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "stc/config.h"
#include "stc/timer.h"
#include "stc/delay.h"
#include "stc/ADC.h"
#include "stc/EEPROM.h"
#include "stc/Exti.h"
#include "stc/GPIO.h"
#include "stc/PCA.h"
#include "stc/soft_uart.h"
#include "stc/USART.h"

#include "bit_ops/bit_ops.h"

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