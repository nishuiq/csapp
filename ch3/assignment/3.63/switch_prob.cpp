/*
理解机器代码中 n - 60 偏移
理解jmpq (,%rsi,8) 以及跳转表的意义，此题就非常简单了
需要注意没有 ret 的 case 会一直往下执行，直到遇到 break 或 default 才停止
*/
long switch_prob(long x, long n) {
    long result = x;
    switch(n) {
        case 60:
        case 62:
            result = x * 8;
            break;
        case 63:
            result = x >> 3;
            break;
        case 64:
            result = (x << 4) - x;
            x = result;
        case 65:
            x = x * x;
        default:
            result = x + 0x4b;
    }
    return result;
}
/*
x in %rdi, n in %rsi
case 64:
    4005b2: 48 89 f8                mov %rdi,%rax       ; result = x
    4005b5: 48 c1 e0 04             shl $0x4,%rax       ; result = x << 4
    4005b9: 48 29 f8                sub %rdi,%rax       ; result = (x << 4) - x
    4005bc: 48 89 c7                mov %rax,%rdi       ; x = result
case 65:
    4005bf: 48 0f af ff             imul %rdi,%rdi      ; x = x * x
case 61/default:
    4005c3: 48 8d 47 4b             lea 0x4b(%rdi),%rax ; result = x + 0x4b
    4005c7: c3                      retq
*/