# void test(long i, b_struct *bp)
# i in %rdi, bp in %rsi
test:
    mov 0x120(%rsi), %ecx         ; ecx = last
    add (%rsi), %ecx              ; ecx = n =  first + last 
    lea (%rdi,%rdi,4), %rax       ; 5i
    lea (%rsi,%rax,8), %rax       ; rax = bp + 40i


    ; 可以看到 bp + 8 是为了跳过 int first，并且采取 8 字节对齐方式
    ; 接着 bp + 8 + 40i 则是 bp->a[i] 其中 40 是其 a[] 的大小，i 是索引值
    ; 因此可以得知 288 = 8 + 7*40，即 CNT = 7
    ; 同时因为到最后会使用到 rdx，推断必然是 ap->idx，所以 idx 一定是第一个变量
    mov 0x8(%rax), %rdx           ; rdx = [bp + 40i + 8] = ap->a[i] = ap->a[i].idx 
    movslq %ecx, %rcx             ; rcx = ecx = n -> long



    ; [bp + 40i + 8idx + 16] = ap->x[ap->idx] = n
    ; bp + 8 + 40i 得到 ap[i]
    ; ap[i] + 8 越过第一个变量
    ; ap[i] + 8 + 8idx = ap[i]->x[idx]
    mov %rcx, 0x10(%rax,%rdx,8)

    retq
A.
    288 = 8 + 7*40，即 CNT = 7

B.
    n 赋值给 ap->x[] 可看出 x[] 为 long
    ap[i] + 8 越过第一个变量 idx，所以 long idx
    又 a[] 大小为 40，x[4]
    8 + 4 * 8 = 40

typedef struct {
    long idx,
    long x[4]
} a_struct


