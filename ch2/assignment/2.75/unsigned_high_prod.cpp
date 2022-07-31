#include <iostream>
using namespace std;

// 库函数，返回一个高w位的补码x*y
int signed_high_prod(int x, int y) {
    int64_t mul = (int64_t) x * y;
    return mul >> 32;
}


/*  
ref https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.75/
如果你不理解，看看这个 https://www.zhihu.com/question/45395026

    P67 P68 有推导，不过是 mod 2^w，这种是截断 w位，我们换成 / 2^w 就得到高w位了
    看起来题目要求我们使用 无符号数与补码乘法的等价性去求解该问题
    
    另
        x' = x + x_{w-1} * 2^w
        y' = y + y_{w-1} * 2^w
    其中
        x' 表示无符号数
        x 表示补码所表示的真值
        x_{w-1} 表示其符号位，当 x < 0 时，作为无符号数则需要加上2^w
    开始计算推导
        (x' * y') / 2^w = [(x + x_{w-1} * 2^w) * y + y_{w-1} * 2^w]
        = [(x * y) + (x * y_{w-1} + y * x_{w-1}) * 2^w + (x_{w-1} * y_{w-1} * 2^2w)] / 2^w
        = (x * y) / 2^w + (x * y_{w-1}) + (y * x_{w-1})
    由于
        (x_{w-1} * y_{w-1} * 2^2w) / 2^w 仍然是 2^w，没法表示，丢弃了

    x' = x + x31 * 2^32
    y' = y + y31 * 2^32
    x'y' = xy + (x31y + y31x) * 2^32 + (x31y31 * 2^64)
    x'y'/2^32 = xy/2^32 + (x31y + y31x) + (x31y31 * 2^32)  2^32没法表示，相当于被取模了，舍弃
    x'y'/2^32 = xy/2^32 + (x31y + y31x)
*/
unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int sign_x = x >> 31 & 1;
    int sign_y = y >> 31 & 1;
    int signed_prod = signed_high_prod(x, y);
    return signed_prod + (x * sign_y) + (y * sign_x);
}

/* a theorically correct version to test unsigned_high_prod func */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

int main()
{
    unsigned x = 0x98765432;
    unsigned y = 0xFFFFFFFF;

    assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;
}