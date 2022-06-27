#ifndef _ADSENSOR_H_
#define _ADSENSOR_H_

#include "../global.h"

/*
    Initalize ADC:
        P1.2 for HALL sensor
        P1.3 for Temperature sensor
        P1.4 for Light sensor
        P1.7 for Button3 and Navigation Button
*/
extern XDATA u8 adc_initialized;
void adc_init();

#endif