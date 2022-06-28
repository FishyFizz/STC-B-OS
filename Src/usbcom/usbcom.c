#include "usbcom.h"
#include "../bit_ops/bit_ops.h"

void usbcom_init(u32 baudrate)
{

    //Set TXD(P31) to Push-Pull RXD(P30) to HiZ
    {
		CLEARBIT(P3M1, 1);
		SETBIT(P3M0, 1);
		
		SETBIT(P3M1, 0);
		CLEARBIT(P3M0, 0);
	}

    //Configure baudrate timer
    {
        IE2  &= ~(1<<2);	//no interrupt
        INT_CLKO &= ~0x04;	//no pin output
        //More work is done by USART_Configuration, according to uart_settings.UART_Baudrate
    }

    //Initialize UART1 on P30 and P31
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
        uart_settings.UART_P_SW = UART1_SW_P30_P31;
        uart_settings.UART_RXD_TXD_Short = DISABLE;
        USART_Configuration(USART1, &uart_settings);
    }

    ES = 1;
}

//this function blocks current process until all data is sent
void __usbcom_write(u8* buf, u8 len)
{
    u8 i;
	
    //Disable interrupt (Tx uses polling mode)
    ES = 0;

    for(i=0;i<len;i++)
    {
        //clear TX end flag
        TI = 0;

        //feed byte into UART1 buffer
        SBUF = buf[i];

        //spin until TX end flag is set (by hardware)
        while(TI == 0);
    }

    //Enable UART1 interrupt
    //(Rx uses interrupt to trigger, but still runs in polling mode)
	RI = 0;//Reset all flags
    TI = 0;
    ES = 1;
}

XDATA u8 usbcom_buf[128];
XDATA u8 usbcom_rxcnt;
XDATA u32 usbcom_timeout;
XDATA u8 usbcom_evtstate = 0;

void usbcom_interrupt (void) interrupt UART1_VECTOR
{
	//Tx uses polling mode, INT source can only be RX

    //Disable UART1 interrupt
    //(Rx uses interrupt to trigger, but still runs in polling mode)
    ES = 0;

    usbcom_rxcnt = 0;
    while(1)
    {
        RI = 0; //Remove RX end flag.
        usbcom_buf[usbcom_rxcnt++] = SBUF; //Retrieve byte.

        //Spin until RX end flag is set (by hardware)
        usbcom_timeout = 500;//You have to try out a proper value for specific baud and clock frequency settings
        while(RI==0) 
        {
            if(--usbcom_timeout == 0)
                goto RX_END;
        }
    }

    RX_END:;
    
    TI = 0;  //Reset all flags
    RI = 0;
    ES = 1; //Enable UART1 interrupt

    usbcom_evtstate = 1;
}