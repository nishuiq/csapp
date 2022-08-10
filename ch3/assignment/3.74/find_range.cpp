#include <iostream>
using namespace std;

typedef enum {NEG, ZERO, POS, OTHER} range_t;

/*
内联 ASM，挺头疼的
*/
range_t find_range(float x) {
    range_t result;
    __asm__(
        "vxorps %%xmm1, %%xmm1, %%xmm1\n\t"
        "movq $0, %%r8\n\t"
        "movq $3, %%r9\n\t"
        "movq $2, %%r10\n\t"
        "movq $1, %%rax\n\t"
        "vucomiss %%xmm1, %%xmm0\n\t"
        "cmova %%r10, %%rax\n\t"  // x > 0
        "cmovb %%r8, %%rax\n\t"   // x < 0
        // "cmove %%r9, %%rax\n\t"  // x = 0
        "cmovp %%r9, %%rax\n\t"   // x = NaN
        "movl %%eax, %0"
        : "=r"(result)
        :
    );
    return result;
}

int main()
{
    range_t n = NEG, z = ZERO, p = POS, o = OTHER;
    cout << find_range(0.0/0.0) << endl;
    cout << find_range(-2.3) << endl;
    cout << find_range(0.0) << endl;
    cout << find_range(3.33) << endl;
    assert(o == find_range(0.0/0.0));
    assert(n == find_range(-2.3));
    assert(z == find_range(0.0));
    assert(p == find_range(3.33));
    return 0;
}

/* 汇编代码
find_range:
    vxorps %xmm1, %xmm1, %xmm1
    movq $0, %r8
    movq $3, %r9
    movq $2, %r10
    movq $1, %rax

    vucomiss %xmm1, %xmm0
    cmova %r10, %rax
    cmovb %r8, %rax
    cmovp %r9, %rax
    ret

*/