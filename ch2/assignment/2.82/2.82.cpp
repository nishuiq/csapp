#include <iostream>
using namespace std;
/*
A.(x<y) == (-x>-y)
    不始终为1
    x=INT_MIN=[1000]，-x=[1000]，此时若y!=INT_MIN，(-x>-y)不成立

B.((x+y)<<4)+y-x==17*y+15*x
    始终为1
    即使溢出，通过移位得到的结果也是一样的

C.~x+~y+1==~(x+y)
    始终为1
    不难想到 
        -x = ~x + 1
        ~x = -x - 1
        左式 ~x + ~y + 1 = (-x-1)+(-y-1) + 1 = -x - y - 1
        右式 ~(x+y) = -(x+y) - 1 = -x - y - 1
        左式 = 右式
        故证毕~

D.(ux-uy) == - (unsigned) (y-x)
    始终为1
    所谓无符号，有符号，不过是对位的不同解释罢了

E. ((x>>2)<<2) <=x
    始终为1
    x为正数显然成立
    x为负数时，后两位被置0，也<=x
*/
int main()
{
    int x = -1;
    printf("0x%x\n", x);
    printf("0x%x\n", x >> 2); printf("%d\n", x >> 2);
    printf("0x%x\n", (x >> 2) << 2);
    cout << ((x >> 2) << 2);
    return 0;
}