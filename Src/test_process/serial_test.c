#include "test_process.h"

void rs485_test()
{
    XDATA u8 buf[4];
    XDATA u32 XDATA* ptr = (u32 XDATA*)buf;

    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_UART2_RECV);
        {
            if(MY_EVENTS & EVT_BTN1_DN)
            {
                *ptr = rand32();
                seg_set_number(*ptr);
                rs485_write(buf, 4);
            }
            else if(MY_EVENTS & EVT_UART2_RECV)
            {
                my_memcpy(buf, rs485_buf, 4);
                seg_set_number(*ptr);
            }
        }
    }
}

void usbcom_test()
{
    XDATA u8 buf[4];
    XDATA u32 XDATA* ptr = (u32 XDATA*)buf;

    while(1)
    {
        wait_on_evts(EVT_BTN1_DN | EVT_UART1_RECV);
        {
            if(MY_EVENTS & EVT_BTN1_DN)
            {
                *ptr = rand32();
                seg_set_number(*ptr);
                usbcom_write(buf, 4);
            }
            else if(MY_EVENTS & EVT_UART1_RECV)
            {
                my_memcpy(buf, usbcom_buf, 4);
                seg_set_number(*ptr);
            }
        }
    }
}
