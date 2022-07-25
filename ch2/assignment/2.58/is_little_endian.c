#include <stdio.h>

typedef unsigned char *byte_pointer;

// 小端为1，大端为0
int is_little_endian() {
    int num = 0xff;
    byte_pointer pointer = (byte_pointer) &num;
    if (pointer[0] == 0xff) return 1;
    return 0;
}


int main()
{
    printf("%d\n", is_little_endian());
    return 0;
}