#include <iostream>
using namespace std;

// 循环左移
unsigned rotate_left(unsigned x, int n) {
/*
    思路：
        [w-n][n]=[xxx][000] n个0
        保留高n位数值，再加回去
        [n][w-n][n]
        左[n]移动到右侧[n]
    注意：
        n=[0,w-1]
        请注意n=0时，w-n=32，有风险，需要拆写
*/
    int w = sizeof(int) << 3;
    // unsigned mask = x >> (w - n);
    // return (x << n)|(mask);
    return (x << n)|(x >> (w - n - 1) >> 1);
}

int main()
{
    printf("0x%x\n", rotate_left(0x12345678, 4));
    printf("0x%x\n", rotate_left(0x12345678, 20));
    printf("0x%x\n", rotate_left(0x12345678, 0));

    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    return 0;
}