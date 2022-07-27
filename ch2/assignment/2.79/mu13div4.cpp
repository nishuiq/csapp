#include <iostream>
using namespace std;

// 此题会用到2.78函数
int mul3div4(int x) {
    x = x + (x << 1);
    int sign = x & INT_MIN;
    sign && (x = x + 1);
    sign && (x = x + (1 << 2) - 1);
    return x >> 2;
}

int main()
{
    int x = 0x87654321;
    assert(mul3div4(x) == x * 3 / 4); 
    return 0;
}