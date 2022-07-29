#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 返回|f|，如果 f = NaN，直接返回f
float_bits float_absva(float_bits f) {
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac) return f;
    // return f ^ 0x80000000;
    return 0 << 31 | exp << 23 | frac;
}

int main()
{
    
    return 0;
}