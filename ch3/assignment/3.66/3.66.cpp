NR(n) = 3n
NC(n) = 4n + 1

初始时
    ...略过部分代码
    movq %rax, %rdi ; %rdi = 3n 此为循环终止条件
    %rcx = A + 8j 为数组索引
    %rdx 为 i
    %r8 = (1 + 4n) << 3 为每行元素偏移
观察发现
    %rcx + %r8 = A + 8j + 8(1 + 4n) = A + 8(1 + 4n + j)
    即可知道 A 的 NC(n) = 1 + 4n

循环终止条件
    cmpq %rdi, %rdx
    jne .L3          ; i - 3n != 0，因此可推导 NR(n) = 3n