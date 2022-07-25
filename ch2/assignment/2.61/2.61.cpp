#include <iostream>
using namespace std;

int A(int x) {
    return !(x ^ -1);
    // return !~x; other solution
    // if x=1111, ~x=0000
}

int B(int x) {
    return !x;
}

int C(int x) {
    return !((x & 0xFF) ^ 0xFF);
    return !~(x|~0xFF);  
    // x=111111XX 这里XX是原来的值 取反=00..
}

int D(int x) {
    return !((x >> 24) & 0xFF);
}


int main()
{
    cout << "A" << endl;
    cout << A(0) << endl;
    cout << A(-1) << endl;

    cout << "B" << endl;
    cout << B(0) << endl;
    cout << B(233) << endl;

    cout << "C" << endl;
    cout << C(0xFFFFFFFF) << endl;
    cout << C(0x12345600) << endl;
    cout << C(0x12345633) << endl;

    cout << "D" << endl;
    cout << D(0x12345600) << endl;
    cout << D(0x12345678) << endl;

    return 0;
}