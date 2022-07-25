#include <iostream>
using namespace std;

// datalab中也有该内容，很相似
int any_odd_one(unsigned x) {
    return !!(x & 0xAAAAAAAA);  // 第2个!将0值转1，将非0值转0
}

int main()
{
    cout << any_odd_one(0xAAA) << endl;
    cout << any_odd_one(233) << endl;
    assert(any_odd_one(0x2));
    assert(!any_odd_one(0x4));
    return 0;
}