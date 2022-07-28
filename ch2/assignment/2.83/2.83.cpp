A.
另 n = 0.yyyyy
n << k = y.yyyy = Y + n
(n << k) - n = Y
Y = n * 2^k - n
Y = n * 2^k - 1
n = Y / (2^k - 1)

思路：
    突然傻了，懂了这道题了。
    Y = B2Uk(y) 可以认为 Y=y 只不过是无符号数
    我们另 n = 0.yyyy
    我们根据题目提示，将小数点右移 k 位
    即 
        n << k = y.yyyy
    而 
        y.yyyy = Y + n （因为Y=y，0.yyyy + y = y.yyyy）
    因此有 
        n << k = Y + n
    接着进行推导
        (n << k) - n = Y
        Y = n * 2^k - n
        Y = n * 2^k - 1
        n = Y / (2^k - 1)

B.
(a)101
    Y = 5, k = 3 ==> n = 5/7
(b)0110
    Y = 6, k = 4 ==> n = 6/15
(c)010011
    Y = 19, k = 6 ==> n = 19/63




