#include <iostream>
using namespace std;

long cread(long *xp) {
    return (xp ? *xp : 0);
}


long cread_alt(long *xp) {
    long tmp = 0;
    xp = xp ? xp : &tmp;
    return *xp;
}

int main()
{
    long a = 0;
    assert(cread(&a) == cread_alt(&a));
    assert(cread(NULL) == cread_alt(NULL));
    return 0;
}

/*
# long cread(long *xp)
# xp in %rdi
cread:
    movq (%rdi), %rax    v = *vp 异常
    testq %rdi, %rdi     Test x
    movl $0, %edx        Set ve = 0
    cmove %rdx, %rax     If x==0, v = ve
    ret                  Return v

# long cread_alt(long* xp)
# xp in %rdi
cread_alt:
  movl $0, %eax
  testq %rdi, %rdi
  cmovne (%rdi), %rax
*/