typedef struct {
    int x[A][B];
    long y;
} str1;

typedef struct {
    char array[B];
    int t;
    short s[A];
    long u;
} str2;

void setVal(str1 *p, str2 *q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1 + v2;
}

# void setVal(str1* p, str2* q)
# p in %rdi, q in %rsi
setVal:
    movslq 8(%rsi), %rax  ; q->t int 需要 4 字节对齐，因此有 4 < B <= 8
    addq 32(%rsi), %rax   ; q->u long 需要 8 字节对齐，因此有 24 < 8 + 4 + 2A <= 32
    ; 8 + 4 是指 int t 的位置 + 4，即 short s[A] 起始地址
    movq %rax, 184(%rdi)  ; 需要 long 8字节对齐 176 < 4 * A * B <= 184
    ret

4 < B <= 8
24 < 8 + 4 + 2A <= 32
176 < 4 * A * B <= 184
A =  9
B = 5