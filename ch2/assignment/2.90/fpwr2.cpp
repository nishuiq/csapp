#include <iostream>
using namespace std;

float u2f(unsigned x) {
    return *(float*) &x;
}
/*
    让我想想。。。
    [s][exp][frac]
    [s][k=8][n=23]

    让我们先思考非规格化形式
        [x][000..0][xxxx]
    最小的非规格化正数则为
        [0][000..0][000...1]
    即
        bias = 2^(8-1) - 1 = 127
        E = 1 - bias = -126
        M = 0.f = 2^(-n)
        V = 2^E * M = 2^(-126) * 2^(-23) = 2^(-149)
    此时知道，这个浮点数所能表示的最小正数范围就是在 2^(-149)
        超出该区域 x < -149，无法表示，返回0.0
        [0][000][000]

    [-149, -126] 非规格化

    接着找出第一个规格化表示
        [x][000..1][xxxx]
    推导
        E = e - bias = 1 - 127 = -126
    于是乎，找到非规划与规格之间的界限
        [-126, ??] 规格化
    再进行推导规格化的最大值E
        [x][111..0][xxxx]
    于是有
        E = (2^8 - 1 - 1) - bias = 254 - 127 = 127
    得到
        [-126, 127] 规格化

    x < -149 太小
        [0][0][0]

    x = [-149, -126) 非规格化
        [x][0][???]
            原本 x = -126 是可以的，但是题目要的是2的指数幂（简单来说就是非规格化 M = 1 无法表示）
            因此[frac]=[000]是必然的，但是 [x][0000][0000] 非规划化如若如此就表示为0了
            只能 2^E * 1
            所以当 x = -126 时只能由规格化去表示（因为非规格化此时不能表示为 *1）

    x = [-126, 127]
        [x][xxxx][xxx]
        因为此时 
            e = [0, 255]
        而
            V = 2^(e-127) * 1 = 2^x
        足以表示
            e = x + 127


*/
float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result 非规格化 */
        exp = 0;
        frac = 1 << (x + 149);  
        // 1<< (x + 149)，当x=-126, n=23 1<< 23 = [1][23个0]，frac位23会污染exp
        // 然而实际上非规格化无法表示x=-126时的情况，因为 M=1 无法表示
    } else if (x < 128) {
        /* Normalized result. */
        exp = x + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 255;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as flat */
    return u2f(u);
}

int main()
{
    assert(fpwr2(0) == powf(2,0));
    assert(fpwr2(100) == powf(2,100));
    assert(fpwr2(-100) == powf(2,-100));
    assert(fpwr2(10000) == powf(2,10000));
    assert(fpwr2(-10000) == powf(2,-10000));
    return 0;
}