64KB 每行 16 字节
64 * 1024 / 16 = 4096块

因为每次循环中
    buffer[i][j].r = 0 都会不命中，此时会把 .r .g .b .a 都放到缓存中
接下来都会命中
    buffer[i][j].g
    buffer[i][j].b
    buffer[i][j].a

不命中率 1/4 = 25%