#include <iostream>
using namespace std;

int lower_one_mask(int n) {
/*  n=[1,w]
    思路：
        [w-n][n]=[00..0][111..1] n个1
*/
    // return (1 << n) - 1; // 这种做法不可行，当n=w异常
    // return (1 << (n - 1) << 1) - 1; // 就可以啦
    int w = sizeof(int) << 3;
    return (unsigned) -1 >> (w - n);
}

int main()
{
    printf("0x%x\n", lower_one_mask(6));
    printf("0x%x\n", lower_one_mask(17));

    assert(lower_one_mask(6) == 0x3F);
    assert(lower_one_mask(17) == 0x1FFFF);
    assert(lower_one_mask(32) == 0xFFFFFFFF);
    return 0;
}