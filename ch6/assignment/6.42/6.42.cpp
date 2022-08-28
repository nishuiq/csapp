与 6.41 类似

char *cptr = (char *) buffer;
for (; cptr < (((char *) buffer) + 640 * 480 * 4); cptr ++)
    *cptr = 0;

其实就是
for (i = 0; i < 640; i++)
    for (j = 0; j < 480; j++)
        buffer[i][j].r = 0;
        buffer[i][j].g = 0;
        buffer[i][j].b = 0;
        buffer[i][j].a = 0;

因为每次循环中
    buffer[i][j].r = 0 都会不命中，此时会把 .r .g .b .a 都放到缓存中
接下来都会命中
    buffer[i][j].g
    buffer[i][j].b
    buffer[i][j].a

不命中率 1/4 = 25%