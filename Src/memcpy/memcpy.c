#include "memcpy.h"

void my_memcpy(u8* to, u8* from, u8 len)
{
    do
    {
        --len;
        to[len] = from[len];
    } while (len);
}