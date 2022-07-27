#include <iostream>
using namespace std;

/*  P71
    最多三个运算
    A. K=17 = 1_0001  = 16 + 1
    B. K=-7 = 1_001   = -8 + 1
    C. K=60 = 11 1100 = 64 - 4
    D. K=—112 = 1_001 0000 = -128 + 16
*/
int A(int x) {
    return (x << 4) + x;
}

int B(int x) {
    return x - (x << 3);
}

int C(int x) {
    return (x << 6) - (x << 2);
}

int D(int x) {
    return (x << 4) - (x << 7);
}

int main()
{
    int x = 0x87654321;
    assert(A(x) == 17 * x);
    assert(B(x) == -7 * x);
    assert(C(x) == 60 * x);
    assert(D(x) == -112 * x);
    return 0;
}