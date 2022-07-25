#include <stdio.h>

typedef unsigned char *byte_pointer;

unsigned replace_byte (unsigned x, int i, unsigned char b) {
    if (i < 0) {
        printf("negative error i ");
        return x;
    }
    if (i > sizeof(unsigned) - 1) {  // 注意sizeof返回是无符号，要小心
        printf("i > unsigned! ");
        return x;
    }
    byte_pointer pointer = (byte_pointer) &x;  
    // [0, w-1] 其中w为字节数 因为数组是按8位1字节偏移的，于是就非常简单了
    pointer[i] = b;
    return x;
}

int main()
{

    printf("0x%x i=%d\n", replace_byte(0x12345678, -1, 0xAB), -1);
    for (int i = 0; i < sizeof(unsigned) + 10; ++ i)
        printf("0x%x i=%d\n", replace_byte(0x12345678, i, 0xAB), i);
    
    
    return 0;
}