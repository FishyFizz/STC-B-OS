#include "rs485.h"
#include "../error/error.h"
#include "../display/seg_led.h"

void rs485_init(u32 baudrate)
{

    //Set TX/DR pins (P37, P47) to Push-Pull, RX pin (P46) to input.
    {
        P4M1 &= 0x3F;	// 0111 1111
        P4M0 |= 0xC0;   // 1000 0000

        P3M1 &= 0x7F;   // 0111 1111
        P3M0 |= 0x80;   // 1000 0000

        P4M1 |= 0x40;   // 0100 0000
        P4M0 &= 0xBF;   // 1011 1111
    }

    //Configure baudrate timer
    {
        IE2  &= ~(1<<2);	//no interrupt
        INT_CLKO &= ~0x04;	//no pin output
        //More work is done by USART_Configuration, according to uart_settings.UART_Baudrate
    }

    //Initialize UART2 on P46 and P47
    {
        XDATA COMx_InitDefine uart_settings;
        uart_settings.UART_Mode = UART_8bit_BRTx;
        uart_settings.UART_BRT_Use = BRT_Timer2;
        uart_settings.UART_BaudRate = baudrate;
        uart_settings.Morecommunicate = DISABLE;
        uart_settings.UART_RxEnable = ENABLE;
        uart_settings.BaudRateDouble = DISABLE; 
        uart_settings.UART_Interrupt = ENABLE;
        uart_settings.UART_Polity = PolityHigh;
        uart_settings.UART_P_SW = UART2_SW_P46_P47;
        uart_settings.UART_RXD_TXD_Short = DISABLE;
        USART_Configuration(USART2, &uart_settings);
    }

    //Tx disable.
    RS485_STATE = RS485_R;

	//Enable interrupt (wait for incoming data)
    IE2 |= 1;
}

//this function blocks current process until all data is sent
void __rs485_write(u8* buf, u8 len)
{
    u8 i;
    //Tx enable.
    RS485_STATE = RS485_D;
    //Disable UART2 interrupt (Tx uses polling mode)
    IE2 &= ~1;

    for(i=0;i<len;i++)
    {
        //clear TX end flag
        S2CON &= ~2;

        //feed byte into UART2 buffer
        S2BUF = buf[i];

        //spin until TX end flag is set (by hardware)
        while((S2CON & 2) == 0);
    }

    //Tx disable.
    RS485_STATE = RS485_R;

    //Enable UART2 interrupt
    //(Rx uses interrupt to trigger, but still runs in polling mode)
    S2CON &= ~1;   //Reset all flags
    S2CON &= ~2;
    IE2 |= 1;
}


XDATA u8 rs485_buf[128];
XDATA u8 rs485_rxcnt;
XDATA u32 rs485_timeout;
XDATA u8 rs485_evtstate = 0;

void rs485_interrupt (void) interrupt UART2_VECTOR
{
	//Tx uses polling mode, INT source can only be RX

    //Disable UART2 interrupt
    //(Rx uses interrupt to trigger, but still runs in polling mode)
    IE2 &= ~1;

    rs485_rxcnt = 0;
    while(1)
    {
        S2CON &= ~1; //Remove RX end flag.
        rs485_buf[rs485_rxcnt++] = S2BUF; //Retrieve byte.

        //Spin until RX end flag is set (by hardware)
        rs485_timeout = 500;//You have to try out a proper value for specific baud and clock frequency settings
        while((S2CON & 1)==0) 
        {
            if(--rs485_timeout == 0)
                goto RX_END;
        }
    }

    RX_END:;
    
    S2CON &= ~1;  //Reset all flags
    S2CON &= ~2;
    IE2 |= 1; //Enable UART2 interrupt

    rs485_evtstate = 1;
}