long decode2(long x, long y, long z) {
    long tmp = y - z;
    return (x * tmp) ^ (tmp << 63 >> 63);
}