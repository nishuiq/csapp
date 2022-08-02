/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x&~y) & ~(x&y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // 验证 x+1 = ~x式子即可得出结论
  // 但是有特殊情况，x=111..1, x+1=0, ~x=0，此时不是Tmax
  /*
    这里的 y 是当 x != -1 时，!y 始终等于 0，用来异或 0 ^ (答案)，这样就能返回正确答案
    当 x = -1 时， !y = 1，此时 1 ^ (答案）
    但是 x = -1 = [11111] x + 1 = [00000] ~x = [00000] 并不是 Tmax
    尽管在 !((~x)^(y)) = 1，但是注意我们的 y = 1
    1 ^ 1 = 0 拒绝答案
    很精妙的过程
  */
  int y = x + 1;
  // printf("%8x %8x %8x %8x %8d\n", x, ~x, x+1, (~x)^(x+1), !((~x)^(x+1)));
  return !y ^ !((~x)^(y));
  //return !(x ^ 0x7FFFFFFF); 如果没有0-255范围要求，可以直接这样。当然可以位移凑出来，就是ops比较多
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // int y = (0xAA << 24) + (0xAA << 16) + (0xAA << 8) + 0xAA;
  int y = (0xAA << 8) + 0xAA;
  y = (y << 16) + y;
  // x&y 先获得只含奇数位01010...(不然会有干扰内容) 再 ^y 去看看是不是一样的
  // 毕竟相当于 y ^ y = 0
  return !((x & y) ^ y);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
    x - 0x30 >= 0 A
    0x39 - x >= 0 B
    判断 A B 符号位
        0 0 true
        0 1 false
        1 0 false
        1 1 false
  */
  int r1 = x + (~0x30 + 1);
  int r2 = 0x39 + (~x + 1);
  // int a = r1 >> 31 & 1;
  // int b = r2 >> 31 & 1;
  int mask = 1 << 31;  // 减少ops
  int a = r1 & mask;
  int b = r2 & mask;
  return !a & !b;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
    x = 0 -> t = 1 -> return z
    x = 1 -> t = 0 -> return y
    t = 1, ~t + 1 = [11..1]
    t = 0, ~t + 1 = [00000]
    我们只需要让 t = 1 时，全1 去 & z 获取值，然后全0 去 & y 丢弃
    同理 t = 0 时，全0 去 & z 丢弃，全1 去 & y 获取值
  */
  int t = !x;
  int tt = ~t + 1;  // 减少ops t = 1 -> tt = [11111]; t = 0 -> tt = [0000]
  // return ((~t + 1) & z) + ((~(!t) + 1) & y);
  return (tt & z) + (~tt & y);  // 减少ops
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
    x <= y 即 y >= x
    Y X C
    0 0 -> 需要计算判断
        0 true
        1 false
    1 1 -> 需要计算判断
        0 true
        1 false
    0 1 -> true
    1 0 -> false
  */
  int sx = x >> 31 & 1;
  int sy = y >> 31 & 1;
  int sxy = sx ^ sy;

  int neg_x = ~x + 1;
  int c = y + neg_x;
  int sc = c >> 31 & 1;
  // 1) 如果是异号，syx=1，根据真值表发现，此时只需要返回sx的值。
  // 2) 如果是同号，syx=0，!syx=1，
  return (sxy & sx) + (!sxy & !sc);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
    题解一：
    此题灵感于第二章家庭作业2.66 leftmost_one
    该做法很暴力，而且非常简单易懂
    就是把最左边的 1，右边全部也染成 1，即 [000][1][xxxx] => [000][1][11111..1]
    之后判断最后一位，如果是 0 那么 x = 0，如果是 1 那么 x != 0
    题解二：
      (x|~x+1)
      x  = 0 (x|~x+1) = [0000]
      x != 0 (x|~x+1) = [1xxxx]
  */
  // solution 1
  // int t;
  // x |= x >> 1;
  // x |= x >> 2;
  // x |= x >> 4;
  // x |= x >> 8;
  // x |= x >> 16;
  // t = x & 1;
  // return (t ^ 1);
  return ((x|(~x+1)) >> 31) + 1;  // solution 2
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* Ref https://zhuanlan.zhihu.com/p/59534845 */
  /*
    本题利用二分法来获取
    [16][16]
        /  \
       [8] [8]
           / \
         [4] [4]
         / \
       [2] [2]
       / \
    [1] [1]
    先看高 16 位是否有值
      如果有，则意味着低 16 位已经被确定了，一定要 16 位来表示
      如果没有，则不位移
    接着把高 16 位移到前面，判断高 8 位是否有值
      如果有，说明需要 8 位来表示
      否则，不需要移位
    以此类推到 1 位

    对于正数而言，只需要统计高位 1 的位置即可
    对于负数，则需要统计高位 0 的位置
      我们可以让负数取反，这样就能把符号位置0，同时顺便一套相同方案处理（都统计高位 1 的位置）
    当然还需要 1 个符号位
  */
  int b16, b8, b4, b2, b1, b0;
  int sign = x >> 31;
  x = (sign & ~x)|(~sign & x);
  // sign=[11111] &~x 负数取反，sign=[0000] ~sign=[1111] & x 正数不变
  b16 = !!(x >> 16) << 4;  // 高16位是否有值
  x >>= b16;  // 高16位有值就继续查看高16位，否则查看低16位
  b8 = !!(x >> 8) << 3;  // 查看这16位中高8位，有值+8，否则为0
  x >>= b8;  // 以此类推...
  b4 = !!(x >> 4) << 2;
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);
  x >>= b1;
  b0 = x;

  return b16 + b8 + b4 + b2 + b1 + b0 + 1;  // 加上符号位
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  /* 本题其实就是家庭作业中的 float_twice */
  /* 这里不再赘述 */
  unsigned sign = uf >> 31 & 1;
  unsigned exp = uf >> 23 & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  if (exp == 0xFF) return uf;  // NaN or Inf
  if (exp == 0) {  // 非规格化
    frac <<= 1;
  } else if (exp == 0xFE) {  // 无法表示了
    exp = 0xFF;
    frac = 0;
  } else {  // 规格化
    exp += 1;
  }
  return sign << 31 | exp << 23 | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  /* 与家庭作业相同的 float_f2i */
  /* 不再赘述 */
  unsigned sign = uf >> 31 & 1;
  unsigned exp = uf >> 23 & 0xFF;
  unsigned frac = uf & 0x7FFFFF;

  int result;
  if (exp == 0xFF) {  // NaN or Inf
    result = 0x80000000;
  } else if (exp < 127) {  // E = [0,31] e = E + 127
    result = 0;  // Too small
  } else if (exp >= 158) {  // Too large e = 158, E = 31, 2^31 * (1+f) > 2^31 - 1
    result = 0x80000000;
  } else {
    unsigned E = exp - 127;
    unsigned M = frac | 0x800000;  // M = 1.f
    if (E >= 23) {  // 无损留下frac
      result = M << (E - 23);
    } else {
      result = M >> (23 - E);
    }
  }
  if (sign) result *= -1;
  return result;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  /* 家庭作业 2.90 fpwr2 */
  unsigned exp, frac;
  unsigned u;

  if (x < -149) {  // 2^(1-127) * 2^(-23) = 2^(-149) 比这个还小就无法表示了
    /* Too small */
    exp = 0;
    frac = 0;
  } else if (x < -126) {
    /* 非规格化 */
    exp = 0;
    frac = 1 << (149 + x);
  } else if (x < 128) {
    /* 规格化 */
    exp = x + 127;
    frac = 0;
  } else {
    /* Too big */
    exp = 0xFF;
    frac = 0;
  }
  u = exp << 23 | frac;
  return u;
}
