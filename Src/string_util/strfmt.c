#include "strfmt.h"

//u32 max = 2147483648 (10 digits) so fmtbuf needs to be 11 bytes
XDATA u8 fmtbuf[FMTBUF_LEN];

XDATA u8 fmt_index;

#define PROTOTYPE_Ux_TO_STR(x)\
void u##x##_to_str(u##x n)\
{\
    fmtbuf[FMTBUF_LEN-1] = '\0';\
    fmtbuf[FMTBUF_LEN-2] = '0';\
\
    fmt_index = FMTBUF_LEN-1;\
    while(n>0)\
    {\
        fmt_index--;\
        fmtbuf[fmt_index] = n%10 + '0';\
        n /= 10;\
    }\
\
    if(fmt_index == FMTBUF_LEN-1) fmt_index = FMTBUF_LEN-2;\
}

//u8/16/32 -> decimal, adaptive length
PROTOTYPE_Ux_TO_STR(8)
PROTOTYPE_Ux_TO_STR(16)
PROTOTYPE_Ux_TO_STR(32)

CODE u8 hexconvert[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

//u8 -> 2 bit hex
void u8_to_str_hex(u8 n) 
{
    fmtbuf[FMTBUF_LEN-1] = '\0';
    fmtbuf[FMTBUF_LEN-2] = '0';
    fmtbuf[FMTBUF_LEN-3] = '0';

    fmt_index = FMTBUF_LEN-1;
    while(n>0)
    {
        fmt_index--;
        fmtbuf[fmt_index] = hexconvert[n%16];
        n /= 16;
    }

    if(fmt_index > FMTBUF_LEN-3) fmt_index = FMTBUF_LEN-3;
}

/*

//u16 -> 4 bit hex
void u16_to_str_hex(u16 n) 
{
    //High Byte
    u8_to_str_hex((n & 0xff00) >> 8);
    fmtbuf[FMTBUF_LEN-5] = fmtbuf[FMTBUF_LEN-3];
    fmtbuf[FMTBUF_LEN-4] = fmtbuf[FMTBUF_LEN-2];

    //Low Byte
    u8_to_str_hex(n & 0xff);

    fmt_index = FMTBUF_LEN - 5;
}

//u32 -> 8 bit hex
void u32_to_str_hex(u32 n) 
{
    //High Word
    u16_to_str_hex((n & 0xffff0000) >> 16);
    fmtbuf[FMTBUF_LEN-7] = fmtbuf[FMTBUF_LEN-5];
    fmtbuf[FMTBUF_LEN-6] = fmtbuf[FMTBUF_LEN-4];
    fmtbuf[FMTBUF_LEN-5] = fmtbuf[FMTBUF_LEN-3];
    fmtbuf[FMTBUF_LEN-4] = fmtbuf[FMTBUF_LEN-2];

    //Low Byte
    u16_to_str_hex(n & 0xffff);

    fmt_index = FMTBUF_LEN - 7;
}

*/