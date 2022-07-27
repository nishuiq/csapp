#include <iostream>
using namespace std;

// 饱和加法返回TMax，负溢出返回TMin
int saturating_add(int x, int y) {
/*
    思路：A + B  =  C
        [+] [+] = [-] 正溢出 001 => TMax
        [-] [-] = [+] 负溢出 110 => TMin
*/
    int sum = x + y;
    int A = x >> 31 & 1;
    int B = x >> 31 & 1;
    int C = sum >> 31 & 1;

    (!A && !B && C) && (sum = INT_MAX);
    (A && B && !C) && (sum = INT_MIN);

    return sum;
}

int main()
{
    assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
    assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
    assert(INT_MIN + INT_MAX == saturating_add(INT_MIN, INT_MAX));
    assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
    return 0;
}