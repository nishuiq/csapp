#include <iostream>
using namespace std;

/* Declaration of data type where 4 bytes are packed 
into an unsigned */ 
typedef unsigned packed_t; 

/* Extract byte from word. Return as signed integer */

/* Failed attempt at xbyte */
/*
    int xbyte(packed_t word, int bytenum) { 
        return (word >> (bytenum << 3)) & 0xFF; 
    }
*/

/*
    思路：
        [8][8][8][8] 组号[3][2][1][0]
        bytenum=[0,3]，我们只需要把需要表示的那一组[]挪到最高位，然后再挪到最低位即可
        该操作需要强转成int类型，这样就是算术右移了
    注意：
        题目要求仅用<<和>>，同时只能使用一次减法！
*/
int xbyte(packed_t word, int bytenum) { 
    return (int) word << ((3 - bytenum) << 3) >> 24;
}

/*
A.[8][8][8][8]每个[]里都是有符号，该代码没有考虑符号位问题
B.xbyte
*/

int main()
{
    assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
    assert(xbyte(0x00112233, 2) == 0x11);
    return 0;
}