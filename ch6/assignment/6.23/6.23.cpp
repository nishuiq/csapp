平均时间 = 寻道时间 + 旋转时间 + 传送时间
T_avg_seek = 4ms
T_avg_rotation = 0.5 * (60s/15000RPM) * 1000ms/s = 2ms
T_avg_transfer = 60/15000 * (1/800) * 1000ms/s = 0.005ms

T_access = T_avg_seek + T_avg_rotation + T_avg_transfer
        = 4ms + 2ms + 0.005ms = 6.005ms
