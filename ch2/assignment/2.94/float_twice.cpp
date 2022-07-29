#include <iostream>
using namespace std;

typedef unsigned float_bits;

// 计算2.0*f，f=NaN，直接返回
/*
    [s][exp][frac]
    思路：
        [x][11111][!=0] NaN 直接返回
        [x][11111][000] Inf 返回
        [x][00000][xxx]
            非规格化
            先判断一下 frac=0.[x]xxxxx 中第一个[x]是0还是1
                若[x] = 0 直接 frac << 1
                若[x] = 1，我们也可以直接 frac << 1
                    之后 exp << 23 | frac （滑向规格化）
                    于是就做到 [x][0001][xx]
        [x][111110][xxx] Inf 返回
            此时无法表示2f，转向Inf
            exp = 0xFF, frac = 0
        [x][00001~11101]
            exp + 1
*/
float_bits float_negate(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) return f;  // NaN or Inf
    if (exp == 0) {  // 非规格化
        frac <<= 1;
        /*        
            这一步非常妙，f = 0.[x]xxx
            当[x] = 0，没问题
            当[x] = 1，位移操作会移到 exp 的域里，相当于 exp+1 了
            而 E 的值不变，f 的值增大2f了
        */
    } else if (exp == 0xFE) {  // Inf
        exp = 0xFF;
        frac = 0;
    } else {  // 规格化
        exp += 1;
    }

    return sign << 31 | exp << 23 | frac;
}

int main()
{
    
    return 0;
}