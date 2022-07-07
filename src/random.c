#include "random.h"

XDATA u32 __rndseed = 0xf2e0062c;

u32 rand32() large reentrant
{
    //LCG: (aX+c)%m
    __rndseed = ((__rndseed * 1103515245) + 12345) & 0x7fffffff;
    return __rndseed;
}


void srand()
{
	XDATA u8 tmp;
	tmp = ds1302_readbyte(DS1302_SEC);
	__rndseed = tmp;
	tmp = ds1302_readbyte(DS1302_MIN);
	__rndseed += tmp;
	tmp = ds1302_readbyte(DS1302_HR);
	__rndseed += tmp;
}
