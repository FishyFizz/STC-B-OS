#include "mem.h"

void my_memcpy(u8* to, u8* from, u8 len)
{
    do
    {
        --len;
        to[len] = from[len];
    } while (len);
}

void memzero(u8* ptr, u8 len)
{
    do
    {
        --len;
        ptr[len] = 0;
    } while (len);
}