#include "adsensor.h"

XDATA u8 adc_initialized = 0;
void adc_init()
{
	XDATA ADC_InitTypeDef adc_settings;
	
    if(adc_initialized)
        return;

    /*
    Initalize ADC:
        P1.2 for HALL sensor
        P1.3 for Temperature sensor
        P1.4 for Light sensor
        P1.7 for Button3 and Navigation Button
    */
    adc_settings.ADC_Px = ADC_P12 | ADC_P13 | ADC_P14 | ADC_P17;
    adc_settings.ADC_Speed = ADC_90T;
    adc_settings.ADC_Power = ENABLE;
    adc_settings.ADC_AdjResult = ADC_RES_H8L2;
    adc_settings.ADC_Polity = PolityLow;
    adc_settings.ADC_Interrupt = DISABLE;

    ADC_Inilize(&adc_settings);

    adc_initialized = 1;
}