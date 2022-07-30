#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 返回|f|，如果 f = NaN，直接返回f
float_bits float_absval(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac) return f;
    // return f ^ 0x80000000;
    return 0 << 31 | exp << 23 | frac;
}

int main()
{
    assert(float_absval(0x89)==0x89);
    assert(float_absval(0x89999999)==0x9999999);
    assert(float_absval(0x7F900000)==0x7F900000);
    return 0;
}