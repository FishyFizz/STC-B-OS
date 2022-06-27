#include "random.h"

XDATA u32 __rndseed = 0xf2e0062c;

u32 rand32() large
{
    //LCG: (aX+c)%m
    __rndseed = ((__rndseed * 1103515245) + 12345) & 0x7fffffff;
    return __rndseed;
}