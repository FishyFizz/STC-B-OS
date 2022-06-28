#include "contextswitch.h"

IDATA u8 __stack[8][16] _at_ 0x80;
DATA u8 __tmp_intframe[16];
XDATA u8 interrupt_frames[8][16];