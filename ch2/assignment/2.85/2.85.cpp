有 k位指数，n为小数，没有符号?
[s][exp][frac]

[exp][frac]
[ k ][ n  ]

bias = 2^(k-1) - 1
E = e - bias
f = [frac]
M = 1 + f = 1.f
V = 2^E * M

A.数7.0
    7.0 = 0111b
    0111b >> 2 ==> 1.11b （为了规格化为1.f）E = 2
    M = 1.11b
    f = 0.11b
    e = bias + E = 2^(k-1) -1 + 2 = 2^(k-1) + 1
    V = 7.0
    [s][exp][frac]
    [0][10...01][1100...000]  k-1是在第k-1位上（从下标0开始）

B.能够被准确描述的最大奇整数
> 此题参考了许多人的答案，答案都不太一样。。。那我按自己想法好了
    我的想法是： P83（参考书中内容）
        n位浮点小数，不能准确描述的最小正整数为
            [1][n个0][1]
            高位的[1]是免费得到的（因为有1.f）
            最后的[1]意思是要得到最小的正整数，因为越往右位权越小，加在[n个0]里面没用（不是最小）
        于是得到
            2^(n+1) + 1
        那么最大的奇整数显然是（假设k足够大，可以表示的阶码范围不会限制这个问题）
            V = 2^(n+1) - 1
        于是乎
            V = 2^E * M 
        进行逆向求值

        我们很容易想到
            f = 0.111...
            M = 1.f
            M = 1.f = 1.11111 = 1 + (1 - 2^(-n)) = 2 - 2^(-n)
        最后求解得到
            E = n
        [0][bias+n][1111...]

C.最小的规格化数的倒数
    先求值
    最小的规格化数
        [s][exp][frac]
        [0][00..1][000]
    显然有
        f = 0.0000
        M = 1.f = 1.0000
        bias = 2^(k-1) - 1
        e = 1
        E = e - bias = 1 - bias
        V = 2^E
    倒数则
        V1 = 2^(-E)
        -E = bias - 1
    接着反向求解 e
    即
        bias - 1 = e - bias
    得
        e = 2 * bias - 1 = 2^k - 3
    此时
        2^k 二进制表示为 1后面跟着k个0
        2^k -1 表示为k个1
        2^k -1 -2 表示为k个1中，把第1位(从0开始)位置0（因为位权2）
        [0][111...101][0000]