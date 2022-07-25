#include <iostream>
using namespace std;

/*
A.移位操作超出w的宽度，该行为是未定义的
B.在32位机器中，int_size_is_32
C.在16位机器中，int_size_is_32_for_16bit
*/

int int_size_is_32() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
    // 不太理解为什么不只用一个beyond_msb去判断
}

int int_size_is_32_for_16bit() {
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int main()
{
    assert(int_size_is_32());
    assert(int_size_is_32_for_16bit());

    return 0;
}