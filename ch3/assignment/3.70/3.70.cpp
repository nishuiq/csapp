proc:
    movq 8(%rdi), %rax   ; rax = *(up + 8) = up->e2.next
    movq (%rax), %rdx    ; rax = *(*(up + 8)) = *(up->e2.next) = 新的nup
    movq (%rdx), %rdx    ; rdx = *(nup.e1.p)

    subq 8(%rax), %rdx   ; rdx = *(nup.e1.p) - *(*(up + 8) + 8)
    ; rdx = *(nup.e1.p) - *(up->e2.next).e1.y

    movq %rdx, (%rdi)    ; up->e2.x = rdx
  ret

union ele {
    struct {
        long *p;
        long y;
    } e1;
    struct {
        long x;
        union ele *next;
    } e2;
};

A.
    e1.p    0
    e1.y    8
    e2.x    0
    e2.next 8

B.
    16 字节

C.
void proc(union ele *up) {
    up->e2.x = *(*(up->e2.next).e1.p) - *(up->e2.next).e1.y;
}