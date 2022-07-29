#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 返回int(f)，若超出表示范围或 NaN，返回 0x80000000=INT_MIN
/*
    e=[127, 158]
    E=[0,31]
*/
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int result = 0x80000000;
    if (exp == 0xFF) return result;  // NaN or Inf

    if (exp == 0) return result;

    if ()





    return sign << 31 | exp << 23 | frac;
}

int main()
{
    
    return 0;
}