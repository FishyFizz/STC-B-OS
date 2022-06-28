#ifndef _STACKSWITCH_H_
#define _STACKSWITCH_H_

#include "../global.h"

extern IDATA u8 __stack[8][16];
extern DATA u8 __tmp_intframe[16];
extern XDATA u8 interrupt_frames[8][16];

#endif //_STACKSWITCH_H_