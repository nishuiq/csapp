#include <iostream>
using namespace std;

// 实现x/2^k
int divide_power2(int x, int k) {
/*  P73
    此题难点在于负数，正数直接x>>k即可
    右移操作是下取整，下取整是小于等于原数
    你可以这样理解：
        正数下取整向0靠近 向下舍入正值
        负数下取整向0远离 向上舍入负值
    负数要加上1才能正常
    或者负数实现上取整，正数下取整
*/
    int sign = x & INT_MIN;
    sign && (x = x + 1);  // 不同于课本上的方法
    // sign && (x = x + (1 << k) - 1);  // 负数上取整  [x/y]=[(x+y-1)/y]

    return x >> k;
}

int main()
{
    // printf("0x%x\n", -9);
    // printf("0x%x\n", -9/2);
    // printf("%d\n", -9/2);
    cout << (-9 >> 1) << endl;

    int x = 0x80000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 2) == x / 4);
    assert(divide_power2(INT_MIN, 3) == INT_MIN / 8);

    x = 0x70000007;
    assert(divide_power2(x, 1) == x / 2);
    assert(divide_power2(x, 3) == x / 8);
    assert(divide_power2(INT_MAX, 3) == INT_MAX / 8);
    return 0;
}