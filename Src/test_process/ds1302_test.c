#include "test_process.h"

void rtc_test()
{
    ds1302_init();

    ds1302_writebyte(DS1302_WP,0x00);
    ds1302_writebyte(DS1302_SEC,0x00);
    sleep(100);
    while(1)
    {
        XDATA u8 sec = 0;
        NOINT_ATOMIC(
            ds1302_readbyte(sec, DS1302_SEC);
            seg_set_number((sec&0x0f) + 10*((sec&0x70)>>4));
        );
        sleep(100);
    }
}