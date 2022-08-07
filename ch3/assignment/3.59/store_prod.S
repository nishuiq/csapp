; 本题目与第二章家庭作业 2.75 类似，使用的是相同的公式，具体看书2.18公式推导

; ux = x + x63 * x^64
; uy = y + y63 * y^64

; ux * uy = (x + x63 * x^64) * (y + y63 * y^64)
;         = 2^64 * (x63y + y63x) + xy + 2^128 * x63 * y63
; 因为 2^128 * x63 * y63 超出128位，丢弃
; 所以
;     ux * uy = 2^64 * (x63y + y63x) + xy
; 所以
;     x * y = ux * uy - 2^64 * (x63y + y63x)

; x63 = 0、-1
; y63 = 0、-1

; void store_prod(int128_t* dest, int64_t x, int64_t y)
; dest in %rdi, x in %rsi, y in %rdx
store_prod:
  movq %rdx, %rax     ; %rax = y
  cqto                ; 符号扩展 %rdx:%rax <- %rax; %rdx = y63
  movq %rsi, %rcx     ; %rcx = x
  sarq $63, %rcx      ; %rcx = x >> 63
  imulq %rax, %rcx    ; %rcx = x63 * y
  imulq %rsi, %rdx    ; %rdx = y63 * x
  addq %rdx, %rcx     ; %rcx = x63 * y + y63 * x
  mulq %rsi           ; %rdx:%rax = ux * %rax = ux * uy
  addq %rcx, %rdx     ; %rdx = %rdx + %rcx = ux * uy(high 8 bits) + (x63 * y + y63 * x)
  ; %rdx = ux * uy(high 8 bits) + (x63 * y + y63 * x) * (2^64)[因为我们是在高64位上操作，因此实际上不需要再乘2^64]
  ; %rdx = ux * uy(high 8 bits) + (x63 * y + y63 * x)
  ; 另外，因为 x63、y63 取值只有 0、-1，因此相当于 ux * uy - (x63 * y + y63 * x)
  movq %rax, (%rdi)   ; set lower 64 bits
  movq %rdx, 8(%rdi)  ; set higher 64 bits
  ret