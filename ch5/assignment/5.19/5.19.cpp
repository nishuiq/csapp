#include <iostream>
// ref https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter5/5.19/
void psum1a(float a[], float p[], long n) {
    long i;
    float last_val, val;
    last_val = p[0] = a[0];
    for (i = 1; i < n; i++) {
        val = last_val + a[i];
        p[i] = val;
        last_val = val;
    }
}

// p[0] = a[0], p[i] = p[i-1] + a[i]
// 3*1a p[i] = p[i-1] + a[i]
void psum3a(float a[], float p[], long n) {
    long i;
    float val = 0;

    for (i = 0; i < n - 2; i += 3) {
        float tmp1 = a[i];
        float tmp2 = tmp1 + a[i+1];
        float tmp3 = tmp2 + a[i+2];

        p[i] = val + tmp1;
        p[i+1] = val + tmp2;
        p[i+2] = val = val + tmp3;
    }

    for (; i < n; i ++) {
        val += a[i];
        p[i] = val;
    }
}


#define LOOP 1000
#define LEN  1000

int main(int argc, char* argv[]) {
    float a[5] = { 1, 2, 3, 4, 5 };
    float p[5];
    psum1a(a, p, 5);
    assert(p[4] == 15);

    float q[5];
    psum3a(a, q, 5);
    assert(q[4] == 15);

    /* for prof */
    for (int i = 0; i < LOOP; i++) {
        float s[LEN];
        float d[LEN];
        psum1a(s, d, LEN);
        psum3a(s, d, LEN);
    }
    return 0;
}