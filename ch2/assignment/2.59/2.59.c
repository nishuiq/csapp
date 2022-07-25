#include <stdio.h>

// (x & 0xFF)|(y & 0xFFFFFF00)
int main()
{
    int x = 0x89ABCDEF, y = 0x76543210;
    int mask = 0xFF;
    int res = (x & mask)|(y & ~mask);
    printf("0x%x\n", res);
    return 0;
}