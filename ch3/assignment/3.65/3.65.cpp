A.
    &A[i][j] -> rdx

B.
    &A[j][i] -> rax

C.
    M = 15
    addq $8, %rdx    ; 很明显是 A[i][j+1]
    addq $120, %rax  ; A[j+1][i]
    8(i * M + j)
    i、j 固定，计算 8M = 120 ==> M = 15