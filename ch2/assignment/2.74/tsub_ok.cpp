#include <iostream>
using namespace std;

// 有datalab味道
// x-y是否溢出，未溢出1，溢出0
int tsub_ok(int x, int y) {
/*
    思路：
        以下为 A + B = C
        [+] [+] = [-] 正溢出 001
        [-] [-] = [+] 负溢出 110
        异号情况不会溢出
    现题目为 A - B，只需要反转 B 即可
*/
    int res = x - y;
    int A = x >> 31 & 1;
    int B = (y >> 31 & 1);
    int C = res >> 31 & 1;
    int pos_over = !A && B && C;
    int neg_over = A && !B && !C;
    return !(pos_over || neg_over);
}

int main()
{
    assert(!tsub_ok(0x00, INT_MIN));
    assert(tsub_ok(0x00, 0x00));

    cout << (INT_MIN + 10 - INT_MIN) << endl;
    assert(tsub_ok(INT_MIN + 10, INT_MIN));

    assert(tsub_ok(INT_MAX, INT_MAX));
    assert(!tsub_ok(INT_MAX, INT_MIN));

    cout << INT_MAX << endl;
    cout << INT_MIN << endl;
    cout << (-1 - INT_MAX) << endl;
    assert(tsub_ok(-1, INT_MAX));

    return 0;
}