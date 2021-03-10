#include <stdio.h>     // printf
#include <stdint.h>    // uint64_t, uint_fast32_t, UINT32_C
#include <inttypes.h>  // PRIuFAST32
#include <stdbool.h>   // bool, true, false
#include <time.h>      // clock_gettime
#include <math.h>      // sqrt

#define BASE (UINT32_C(7)) 
#define MOD  (UINT32_C(20201227))

typedef struct {
    uint_fast32_t exp;
    uint_fast32_t log;
} EXPLOG, *PEXPLOG;

static double timer(void)
{
    static bool start = true;
    static struct timespec t0;
    struct timespec t1;

    if (start) {
        start = false;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        return 0;
    } else {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        start = true;
        return 1.0 * t1.tv_sec + 1e-9 * t1.tv_nsec - (1.0 * t0.tv_sec + 1e-9 * t0.tv_nsec);
    }
}

// Naive discrete logarithm by trial multiplication
// return e where BASE^e (mod MOD) = h
static uint_fast32_t discrlog1(uint_fast32_t h)
{
    uint_fast32_t e = 0, k = 1U;
    while (k != h) {              // the target is h
        k = k * BASE % MOD;       // all 32-bit numbers (BASE: 3bit, MOD: 25bit => k * BASE 28bit)
        ++e;                      // exponent = multiplication count
    }
    return e;
}

// Naive discrete logarithm by trial multiplication
// return {e,p} where BASE^e (mod MOD) = p
//     or {e,q} where BASE^e (mod MOD) = q
// whichever e is smaller
static EXPLOG discrlog2(uint_fast32_t p, uint_fast32_t q)
{
    uint_fast32_t e = 0, k = 1U;
    while (k != p && k != q) {    // symmetry in p, q
        k = k * BASE % MOD;       // all 32-bit numbers (BASE: 3bit, MOD: 25bit => k * BASE 28bit)
        ++e;                      // exponent = multiplication count
    }
    return (EXPLOG){e, k == p ? p : q};   // use the other one for next calc
}

static void ext_gcd(int_fast32_t a, int_fast32_t b)
{
    int_fast32_t q, tmp, r0 = a, r = b, s0 = 1, s = 0, t0 = 0, t = 1;

    while (r) {
        q = r0 / r;
        tmp = r0 - q * r; r0 = r; r = tmp;
        tmp = s0 - q * s; s0 = s; s = tmp;
        tmp = t0 - q * t; t0 = t; t = tmp;
    }
    printf("Bezout coefficients     : %i %i\n", s0, t0);
    printf("Greatest common divisor : %i\n", r0);
    printf("Quotients by the gcd    : %i %i\n", t, s);
}

static void pollardrho(uint_fast32_t beta)
{
    static const uint_fast32_t alpha = BASE, N = MOD, n = (MOD - 1);
    uint_fast32_t i, x = 1, a = 0, b = 0, X = 1, A = 0, B = 0;

    for (i = 1; i < n; ++i) {
        switch (x % 3) {
            case 0: x = x * x     % N; a =  a*2  % n; b =  b*2  % n; break;
            case 1: x = x * alpha % N; a = (a+1) % n;                break;
            case 2: x = x * beta  % N;                b = (b+1) % n; break;
        }
        switch (X % 3) {
            case 0: X = X * X     % N; A =  A*2  % n; B =  B*2  % n; break;
            case 1: X = X * alpha % N; A = (A+1) % n;                break;
            case 2: X = X * beta  % N;                B = (B+1) % n; break;
        }
        switch (X % 3) {
            case 0: X = X * X     % N; A =  A*2  % n; B =  B*2  % n; break;
            case 1: X = X * alpha % N; A = (A+1) % n;                break;
            case 2: X = X * beta  % N;                B = (B+1) % n; break;
        }
        if (x == X) break;
    }
    printf("i,n   : %8u %8u\n", i, n);
    printf("x,a,b : %8u %8u %8u\n", x, a, b);
    printf("X,A,B : %8u %8u %8u\n", X, A, B);

    uint_fast32_t p, q;
    if (B >= b) {
        p = B - b;
    } else {
        p = n - b + B;
    }
    if (a >= A) {
        q = a - A;
    } else {
        q = n - A + a;
    }
    printf("p,q   : %8u %8u\n", p, q);
    ext_gcd(p, q);
}

// static uint_fast32_t babygiant(uint_fast32_t h)
// {
//     static const uint_fast32_t m = (uint_fast32_t)ceil(sqrt(MOD));
//     static bool maketable = true;

// }

static uint_fast32_t nextpow2(uint_fast32_t num)
{
    uint_fast32_t count = 0;
    while (num) {
        num >>= 1;
        ++count;
    }
    return (1 << count) % MOD;
}

static void result(uint_fast32_t p, uint_fast32_t q)
{
    int i, warmup = 3, loop = 100;
    volatile uint_fast32_t r1 = {0}, r2 = {0};
    double t, t1 = 0, t2 = 0, t1min = 10, t2min = 10, t1max = 0, t2max = 0;

    for (i = 0; i < warmup; ++i) {
        r1 = discrlog1(p);
        r2 = discrlog1(q);
    }
    for (i = 0; i < loop; ++i) {
        timer(); r1 = discrlog1(p); t = timer(); if (t < t1min) { t1min = t; } if (t > t1max) { t1max = t; } t1 += t;
        timer(); r2 = discrlog1(q); t = timer(); if (t < t2min) { t2min = t; } if (t > t2max) { t2max = t; } t2 += t;
    }
    printf("  %"PRIu32" ^%8"PRIuFAST32" = %8"PRIuFAST32" (min %.5f avg %.5f max %.5f s)\n", BASE, r1, p, t1min, t1 / loop, t1max);
    printf("  %"PRIu32" ^%8"PRIuFAST32" = %8"PRIuFAST32" (min %.5f avg %.5f max %.5f s)\n", BASE, r2, q, t2min, t2 / loop, t2max);
}

int main(void)
{
    ext_gcd(23158, 166667);
    // pollardrho(15113849);

    // printf("\nalgorithm (ednl)\n");
    // result(15113849, 4206373);

    // printf("\nejolson\n");
    // result(6270530, 14540258);

    // printf("\nlurk101\n");
    // result(16915772, 18447943);

    // printf("\n");
    return 0;
}
