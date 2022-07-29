#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 0.5*f，与2.94题相反
/*
    本题难度在于四舍五入，末两位，半值 2^1/2 = 1 = 1b
    00 >>
    01 >>
    10 >>
    11 >>  +1 要进1

特殊点
    [s][exp][frac]
    当 exp = 0 时
        先记录[frac] 末2位数，根据半值 2^1/2 = 1 = 01b
        仅当为 11b 才四舍五入，即+1
        之后右移操作 >> [exp][frac]
        接着根据四舍五入考虑+1
    你很可能会疑惑的问题
        为什么要把 exp 和 frac 同时位移操作？
            因为当前是规格化数，2^E * (1 + f)
            我们不能只把 f 变成 0.5f，所以必须把 exp 也位移操作
            这样就变成 2^E * (0.5f)，但这种 0.5f 是有可能精度损失

            另外值得一提的是，四舍五入+1有可能又变回规格化数
            [001][1111] >> 1 ==> [000][1111] + 1 ==> [001][0000]
            换个思路，frac=[1111]全1，近似等于1，
                [ 2^E * (1 + 1) ] * 0.5 = 2^E
*/
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned rest = f & 0x7FFFFFFF;

    int addition = (frac & 0x3) == 0x3;

    if (exp = 0xFF) return f;  // NaN or Inf
    if (exp == 0) {  // 非规格化
        frac >>= 1;
        frac += addition;
    } else if (exp == 1) {
        rest >>= 1;
        rest += addition;
        exp = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
    } else {
        exp -= 1;
    }

    return sign << 31 | exp << 23 | frac;
}

int main()
{
    
    return 0;
}