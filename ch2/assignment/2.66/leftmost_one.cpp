#include <iostream>
using namespace std;

// https://stackoverflow.com/a/12416620
// 得到x最左边是1的码
int leftmost_one(unsigned x) {
/*
    这道题与2.65相似
    比较好的思考：
        首先，因为最高位1位只能是它本身，它的值已经是定值，因此x>>1跳过它
        跳过是指这个位不需要 or 了
        之后，因为最高位2位已成定值， x>>2跳过它
        之后，因为最高位4位已成定值， x>>4条过它
        之后，因为最高位8位已成定值， x>>8条过它
        之后，因为最高位16位已成定值，x>>16条过它
        这样得到了[000..111..]
*/
    printf("org  0x%x\n", x);
    x |= x >> 1; printf("test 0x%x\n", x);
    x |= x >> 2; printf("test 0x%x\n", x);
    x |= x >> 4; printf("test 0x%x\n", x);
    x |= x >> 8; printf("test 0x%x\n", x);
    x |= x >> 16; printf("test 0x%x\n\n", x);
    return x ^ (x >> 1);
}

int main()
{
    printf("0x%x\n", leftmost_one(0xA4224121));
    printf("0x%x\n", leftmost_one(0x6600));

    assert(leftmost_one(0xFF00) == 0x8000);
    assert(leftmost_one(0x6000) == 0x4000);
    assert(leftmost_one(0x0) == 0x0);
    assert(leftmost_one(0x80000000) == 0x80000000);
    return 0;
}