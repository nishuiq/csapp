2048/32 = 64块

1个块中32字节，可存放 【 square[0][0] | square[0][1] 】

注意到 square[16][16] 16 * 16 * 16 = 4096，是 2048 高速缓存的 2 倍

A.
    16 * 16 * 4 = 1024

B.
    前 8 次内循环，第一个写不命中，就会把接下来 3 个元素放入缓存中
    后 8 次内循环，会把前面循环的内容覆盖掉

    16 * 16 * 4 / 4 = 256

C.
    1/4 = 25%