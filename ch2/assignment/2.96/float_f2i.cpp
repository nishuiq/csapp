#include <iostream>
using namespace std;

typedef unsigned float_bits;

float u2f(unsigned u) {
    return *(float *)&u;
}

// 返回int(f)，若超出表示范围或 NaN，返回 0x80000000 = INT_MIN
/*
    E = e - bias = e - 127
    由于该范围 int 只能表示这么多
        E = [0, 31]
    反向求值 e
        e = [127, 158]
    
    exp < 127 无法表示，最接近 0
        res = 0
    exp >= 158 无法表示，超出 int 范围
        res = INT_MIN
    exp = [127, 158)
        由于 frac 有 23 位小数，并且是 1.f，因此实际有1位+23位小数
        需要在 frac = frac | 1 << 23 加上
        判断一下 E，看看这 23 位小数能不能留下来
            E = e - bias
        E >= 23
            frac << (E - 23)
        E < 23
            frac >> (23 - E)

*/
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int result;
    // if (exp == 0xFF) return result;  // NaN or Inf

    if (exp < 127) {
        result = 0;
    } else if (exp >= 158) {
        result = 0x80000000;
    } else {
        unsigned E = exp - 127;
        unsigned M = frac | 0x800000;  // M = 1.f
        if (E >= 23) {
            result = frac << (E - 23);
        } else {
            result = frac >> (23 - E);
        }
    }
    return sign ? -result : result;
}

int main()
{
    assert(float_f2i(0x98765432) == (int)u2f(0x98765432));
    assert(float_f2i(0x19802385) == (int)u2f(0x19802385));
    assert(float_f2i(0x78000087) == 0x80000000);
    assert(float_f2i(0x8F088888) == (int)u2f(0x8F088888));
    return 0;
}