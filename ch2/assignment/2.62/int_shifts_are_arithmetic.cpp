#include <iostream>
using namespace std;

int int_shifts_are_arithmetic() {
    // int x = 1 << 31;
    // return !(((x >> 31) & 0xFF) ^ 0xFF);
    int x = -1;
    return !(x ^ (x >> 1));  // 如果是算术右移，那么x^(x>>1)=0，否则x^(x>>1)=100...
}

int main()
{
    cout << int_shifts_are_arithmetic() << endl;
    return 0;
}