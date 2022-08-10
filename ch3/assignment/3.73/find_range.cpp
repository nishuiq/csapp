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
        "vucomiss %%xmm0, %%xmm1\n\t"
        "jp .P\n\t"
        "ja .A\n\t"
        "jb .B\n\t"
        "je .C\n\t"
        ".A:\n\t"
        "movl $0, %%eax\n\t"
        "jmp .done\n\t"
        ".B:\n\t"
        "movl $2, %%eax\n\t"
        "jmp .done\n\t"
        ".C:\n\t"
        "movl $1, %%eax\n\t"
        "jmp .done\n\t"
        ".P:\n\t"
        "movl $3, %%eax\n\t"
        ".done:\n\t"
        "movl %%eax, %0"    // %0 占位符，表示 result
        : "=r"(result)      // 将 %eax 输出给 result
        // asm("code" :output :input : clobber/modify)
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
    vucomiss %xmm0, %xmm1
    jp .P
    ja .A
    jb .B
    je .C
    .A:
        movl $0, %eax
        jmp .done
    .B:
        movl $2, %eax
        jmp .done
    .C:
        movl $1, %eax
        jmp .done
    .P:
        movl $3, %eax
    .done:
        rep; ret
*/