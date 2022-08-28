
T_avg_seek = 4ms
T_avg_rotation = 0.5 * (60/15000) * 1000ms/s = 2ms
T_max_rotation = 4ms

计量单位混乱。。。
那就按照我自己的思路：
2MB = 2 * 2^20 B
2MB/512B = 4096块扇区，需要5次


A.
    (T_avg_seek + T_avg_rotation) + 5 * T_max_rotation
    = 4 + 2 + 5 * 4 = 26ms
B.
    (T_avg_seek + T_avg_rotation) * 4096
    = 24576ms = 24.576s