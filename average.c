#include <stdint.h>
#include <stdio.h>

uint32_t average1(uint32_t a, uint32_t b)
{
    return (a >> 1) + (b >> 1) + (a & b & 1);
}

uint32_t average2(uint32_t a, uint32_t b)
{
    return (a & b) + ((a ^ b) >> 1);
}

int main()
{
    uint32_t c = average1(513, 41);
    return 0;
}