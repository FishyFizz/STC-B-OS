#ifndef _STRFMT_H_
#define _STRFMT_H_

#include "../global.h"

#define FMTBUF_LEN 11

extern XDATA u8 fmtbuf[FMTBUF_LEN];
extern XDATA u8 fmt_index;
extern XDATA u8 __fmt_tmp[2];

void u8_to_str(u8 n);
void u16_to_str(u16 n);
void u32_to_str(u32 n);
void u8_to_str_hex(u8 n);

#define u16_to_str_hex(n)\
{\
    u8_to_str_hex((n & 0xff00) >> 8);\
    fmtbuf[FMTBUF_LEN-5] = fmtbuf[FMTBUF_LEN-3];\
    fmtbuf[FMTBUF_LEN-4] = fmtbuf[FMTBUF_LEN-2];\
    u8_to_str_hex(n & 0xff);\
    fmt_index = FMTBUF_LEN - 5;\
}

#define u32_to_str_hex(n)\
{\
    u16_to_str_hex((n & 0xffff0000) >> 16);\
    fmtbuf[FMTBUF_LEN-9] = fmtbuf[FMTBUF_LEN-5];\
    fmtbuf[FMTBUF_LEN-8] = fmtbuf[FMTBUF_LEN-4];\
    fmtbuf[FMTBUF_LEN-7] = fmtbuf[FMTBUF_LEN-3];\
    fmtbuf[FMTBUF_LEN-6] = fmtbuf[FMTBUF_LEN-2];\
    u16_to_str_hex(n & 0xffff);\
    fmt_index = FMTBUF_LEN - 9;\
}

/*
    After calling these conversion functions,
    fmtbuf[fmt_index] will be the string converted.
*/

#endif