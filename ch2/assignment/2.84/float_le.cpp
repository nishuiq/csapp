#include <iostream>
using namespace std;

unsigned f2u(float x) {
    return *(unsigned*)&x;
}

/*
    思路：
        这道题是把浮点数转成无符号数，
        虽然说是无符号数，但是我们转换后认为其高1位是符号位
        因此 [s][xxx]

        考虑+0/-0
            把符号位左移掉，看看后面的数值是否相同，是否为0
        考虑符号位 x y
            10 x < y 显然成立
            01 x > y 显然成立
            00 判断 x <= y
            11 判断 x >= y (因为高位为1表示负数，但在无符号里则是正权值)  
*/
// x<=y，+-0认为相等
int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (ux << 1 == 0 && uy << 1 == 0) ||  // [s][0000]
        (sx && !sy) ||                        // 01
        (!sx && !sy && ux <= uy) ||           // 00 ux <= uy
        (sx && sy && ux >= uy);               // 11 ux >= uy
}

int main()
{
    assert(float_le(-0, +0));
    assert(float_le(+0, -0));
    assert(float_le(0, 3));
    assert(float_le(-4, -0));
    assert(float_le(-4, 4));
    return 0;
}