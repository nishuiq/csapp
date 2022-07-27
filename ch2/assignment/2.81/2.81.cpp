#include <iostream>
using namespace std;

/*
    思路：
        [w-k][k]=[111][000] k个0
        直接-1左移k把低k位置0即可
*/
int funcA(int k) {
    return -1 << k;
}

/*
    思路：
        [w-k-j][k][j]=[000][111][000]
        先-1左移k，然后取反，再左移j
            [1111] << k = [1111][k个0]
            ~[1111][k个0] = [0000][k个1]
            [0000][k个1] << j = [0000][k个1][j个0]
*/
int funcB(int j, int k) {
    return ~(-1 << k) << j;
}

/* 题目要求不允许有参数w
A.funcA 1^(w-k) 0^k
B.funcB 0^(w-k-j) 1^k 0^j
*/
int main()
{
    printf("0x%x\n", funcA(3));
    printf("0x%x\n", funcB(8,16));

    assert(funcA(8) == 0xFFFFFF00);
    assert(funcB(8, 16) == 0x00FFFF00);
    return 0;
}