#include <iostream>
using namespace std;
/*
ref 受其启发，补上了向0舍入的细节。。。
    http://disq.us/p/28yuort
    [s][M]=[x][xxxxx]

向零舍入
    正数，向下舍入 2.5->2
    负数，向上舍入 -1.5->-1

在实际运算中，当我们 x - [x/4] 时，产生的结果是含有小数点的，此时我们是需要四舍五入的

正数时
    [x/4] 会带有小数
    当我们 x - [x/4] 时，会因为小数而借位-1
    因此我们有必要让 [x/4]向上取整

    向上取整的公式是：x/y = (x+y-1)/y = (x+4-1)/4 = ((x + (1 << 2) - 1)) >> 2

负数时
    与正数同理，只不过负数右移操作本身就是向上取整
*/
// [3x/4]，不会溢出，向零舍入
int threefourths(int x) {
    int is_neg = x & INT_MIN;
    int quarter = x;
    !(x & is_neg) && (quarter += 3);
    quarter >>= 2;
    // printf("x = [%3d]; qua = [%3d]; x - qua= [%3d]\n", x, quarter, x - quarter);
    return x - quarter;
}

int main()
{
    assert(threefourths(8) == 6);
    assert(threefourths(9) == 6);
    assert(threefourths(10) == 7);
    assert(threefourths(11) == 8);
    assert(threefourths(12) == 9);

    assert(threefourths(-8) == -6);
    assert(threefourths(-9) == -6);
    assert(threefourths(-10) == -7);
    assert(threefourths(-11) == -8);
    assert(threefourths(-12) == -9);
    return 0;
}