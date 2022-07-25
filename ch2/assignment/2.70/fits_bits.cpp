#include <iostream>
using namespace std;


// 当 x 可以表示为 n 位、2 的补码时返回 1
// 就是转换成n位补码是否可以表示x
int fits_bits(int x, int n) {
/*
    [w-n][n]=[000|111][xxx]
    把高n位清空
        如果x是正数，且第n位刚好是1，左移+右移将变成111..[n]，则n-bit表示的是负数，显然不等于x
        如果x是负数，

    并与x进行比较
    
*/
    // return !(x ^ (1 << n));  //这种方式不可行，因为n可能超过x的最高位1的位置，导致错误
    int w = sizeof(int) << 3;
    int offset = w - n;
    printf("0x%x\n", x << offset);
    printf("0x%x\n", x << offset >> offset);
    return (x << offset >> offset) == x;
    // return !((x << offset >> offset) ^ x);  //不能用==则替换成这个
}

int main()
{
    cout << (~0b11) << endl;
    cout << fits_bits(128, 8) << endl;
    // assert(!fits_bits(0xFF, 8));
    // assert(!fits_bits(~0xFF, 8));

    // assert(fits_bits(0b0010, 3));

    // assert(!fits_bits(0b1010, 3));
    // assert(!fits_bits(0b0110, 3));

    // assert(fits_bits(~0b11, 3));

    // assert(!fits_bits(~0b01000011, 3));
    // assert(!fits_bits(~0b111, 3));

    return 0;
}