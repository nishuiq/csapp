#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 返回(float)i，
/*
Ref:
https://valineliu.gitbook.io/deuterium-wiki/reading/cs-jing-dian-shu-ji/csapp-3e-homework-solution/2.-representing-and-manipulating-information/2.97-float-i2f
https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.97/

此题难点在于四舍五入上
    先特判 
        i = 0
        i = INT_MIN
    然后很容易想到 frac 只有23位，规格化后 M = 1.f 相当于 24位
    因此 bits_length(i) = 24 是其分类讨论的界限

    int i = [sign][num]
    因为 M = 1.f 可表示 24 位，其中 f小数有 23 位
    因此我们需要以该数作为界限
    令
        bits = i 的位数（不包括符号位）
        fbits = bits - 1 （表示需要的frac位数）
    fbits <= 23 小于该范围，无损保留 i 的数值，
        frac << (23 - fbits)

    fbits > 23 已超出 fbits 所能表示的数字，因此需要考虑四舍五入
        计算需要舍入的位数
            int offset = fbits - 23
        计算半值
            int round_mid = 1 << (offset - 1)  2^k/2 k=位数
        获取末尾 offset 个数
            int round_part = frac & bits_mask(offset)

        试比较
            round_part < round_mid 不需要+1
            round_part > round_mid 需要+1
            round_part == round_mid
                判断获取round_part前面一位的数 [x][round_part]
                [x] = 0 不需要+1
                [x] = 1 需要+1 （向偶舍入）

*/

// 返回 i 需要多少位才能表示
int bits_length(int i) {
    if (i & INT_MIN) return 32;

    unsigned u = (unsigned) i;
    int length = 0;
    while (u >= (1 << length)) {
        ++ length;
    }
    return length;
}

// l个1 [w-l][l]=[000][11111]
unsigned bits_mask(int l) {
    return (unsigned) -1 >> (32 - l);
}

float_bits float_i2f(int i) {
    unsigned sign, exp, frac, exp_sig, rest;
    unsigned fbits, bits;
    unsigned bias = 0x7F;

    if (i == 0) {
        sign = 0;
        exp = 0;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    } else if (i == INT_MIN) {
        sign = 1;
        exp = 31 + bias;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    }

    sign = 0;
    if (i < 0) {
        sign = 1;
        i = -i;
    }

    bits = bits_length(i);
    fbits = bits - 1;
    exp = fbits + bias;

    rest = i & bits_mask(fbits);  // 抛弃1位，作为1.fbits
    if (fbits <= 23) {
        frac = rest << (23 - fbits);
        exp_sig = exp << 23 | frac;
    } else {
        int offset = fbits - 23;  // 要丢弃的位数k
        int round_mid = 1 << (offset - 1);  // 半值，2^k/2
        int round_part = rest & bits_mask(offset);  // 留下低k位
        frac = rest >> offset;
        exp_sig = exp << 23 | frac;

        if (round_part < round_mid) {
            /* Nothing to do */
        } else if (round_part > round_mid) {
            exp_sig += 1;
        } else {
            if (frac & 1) {  // 向偶舍入
                exp_sig += 1;
            }
        }
    }

    return sign << 31 | exp_sig;
}

int main()
{
    /* Test bits_length */
    assert(bits_length(-1) == 32);
    assert(bits_length(INT_MIN) == 32);
    assert(bits_length(0) == 0);
    assert(bits_length(3) == 2);
    assert(bits_length(23) == 5);

    /* Test bits_mask */
    assert(bits_mask(3) == 0x7);
    assert(bits_mask(9) == 0x1FF);
    assert(bits_mask(31) == 0x7FFFFFFF);

    /* Test float_i2f */
    assert(float_i2f(0) == 0x0);
    assert(float_i2f(INT_MIN) == 0xCF000000);
    assert(float_i2f(0x00359141) == 0x4A564504);
    assert(float_i2f(-98765) == 0xC7C0E680);
    return 0;
}