#include <iostream>
// ref https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter5/5.17/
void* basic_memset(void *s, int c, size_t n) {
    size_t cnt = 0;
    unsigned char *schar = (unsigned char *)s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

/*
先找到是k的倍数的地址，在此前用char一个个填充
然后用 unsigned long 来进行 8 字节填充，
最后不足 8 字节内容就由char继续填充
注意 8 字节替换成 sizeof(unsigned long)
*/
void *effective_memset(void *s, unsigned long c, size_t n) {
    size_t cnt = 0;
    size_t k = sizeof(unsigned long);
    unsigned char *schar = (unsigned char *)s;

    while (cnt < n) {
        if ((size_t)schar % k == 0) break;
        *schar++ = (unsigned char) c;
        cnt ++;
    }

    size_t res = n - cnt;
    size_t loop = res / k;
    size_t left = res % k;

    unsigned long *slong = (unsigned long *)schar;

    for (size_t i = 0; i < loop; i ++) {
        *slong++ = c;
    }

    schar = (unsigned char*)slong;
    for (size_t i = 0; i < left; i ++) {
        *schar++ = (unsigned char)c;
    }

    return s;
}

int main()
{
    size_t space = sizeof(char) * 65537;

    void* basic_space = malloc(space);
    void* effective_space = malloc(space);

    int basic_fill = 0xFF;
    unsigned long effective_fill = ~0;

    basic_memset(basic_space, basic_fill, space);
    effective_memset(effective_space, effective_fill, space);

    assert(memcmp(basic_space, effective_space, space) == 0);

    free(basic_space);
    free(effective_space);
    return 0;
}