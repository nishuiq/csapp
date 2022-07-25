#include <iostream>
using namespace std;

unsigned srl(unsigned x, int k) {
    unsigned xsra = (int) x >> k;
/*
    本质上就是把高k位置0
    思路1：
        右移k位，相当于要把高位k个数置0，可 (1<<(w-k))-1 即可 [k][w-k]=[0000][1111]，之后&即可
    思路2：
        跟思路1一样，不过是变成-1，然后移位操作，接着有[k][w-k]=[1111][0000]，然后取反
*/
    /* solution 2 */
    // int w = sizeof(int) << 3;  // 8*int
    // int mask = (int) -1 << (w - k);  // 相当于把高k位留下为1，然后取反~mask=0000(k-1)11111
    // return xsra & (~mask);

    /* solution 1 */
    int w = 8*sizeof(int);
    int mask = (1 << (w-k)) - 1;
    return xsra & mask;
}

int sra(int x, int k) {
    int xsrl = (unsigned) x >> k;
/*
    [k][w-k]=[1111][0000] or 上即可
*/
    int w = sizeof(int) << 3;
    int flag = (unsigned) x >> 31 & 1;
    int mask = (flag << (w-k)) - 1;  // 可在srl思路1找到灵感
    return xsrl|(~mask);
}

int main()
{
    unsigned test_unsigned = 0x12345678;
    int test_int = 0x12345678;
    int test_neg_int = 0xB554D9A6;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);
    assert(sra(test_neg_int, 4) == test_neg_int >> 4);

    test_unsigned = 0x87654321;
    test_int = 0x87654321;
    assert (srl (test_unsigned, 4) == test_unsigned >> 4);
    assert (sra (test_int, 4) == test_int >> 4);


    return 0;
}