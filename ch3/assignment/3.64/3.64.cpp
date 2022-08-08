A.
    A[R][S][T]
    A[i][j][k]
    公式：
    Xa + L(i*S*T + j*T + k)

B.
; i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:
    leaq     (%rsi,%rsi,2), %rax    ; rax = j + j * 2 = 3j
    leaq     (%rsi,%rax,4), %rax    ; rax = j + (3j) * 4 = 13j
    movq     %rdi, %rsi             ; j = i
    salq     $6, %rsi               ; j = i << 6 = i/64
    addq     %rsi, %rdi             ; i = i + j = i + i/64 = i * 65/64
    addq     %rax, %rdi             ; i = i + rax = i * 65/64 + 13j
    addq     %rdi, %rdx             ; k = k + rdi = i * 65/64 + 13j + k
    movq     A(,%rdx,8), %rax       ; [Xa + 8*(A + rdx)]
    movq     %rax, (%rcx)           ; *dest = rax
    movl     $3640, %eax            ; eax = 3640 sizeof(A) = 3640
    ret
R = 7 (3640/8/13/5)
S = 5 (i * 65/13，取舍变成 i * 65)
T = 13(13j)