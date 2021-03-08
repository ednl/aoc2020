// As /u/mebeim writes at
// https://www.reddit.com/r/adventofcode/comments/kjtg7y/2020_day_25_solutions/ggz4bpl/
// the problem can be rephased in terms of the Diffie-Hellman key exchange algorithm:
// "Given the public base g = 7, the public modulus p = 20201227, and the two public keys A and B
// (obtained as A = g^a mod p, B = g^b mod p), calculate the secret key s = A^b mod p = B^a mod p."
// Ref. https://en.wikipedia.org/wiki/Diffie-Hellman_key_exchange

// My version: pick the earliest matching key (p or q) in the loop,
// then use the loop count (e) with the other key (q or p) to
// calculate the secret key with modular exponentiation.

#include <stdio.h>     // printf
#include <stdint.h>    // uint64_t, UINT64_C
#include <inttypes.h>  // PRIu64
#include <stdbool.h>   // bool, true, false
#include <time.h>      // clock_gettime

#define BASE (UINT64_C(7)) 
#define MOD  (UINT64_C(20201227))

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

static uint64_t dhke(uint64_t p, uint64_t q)
{
    uint64_t e = 0, k = 1U;
    while (k != p && k != q) {  // symmetry in p, q
        k = k * BASE % MOD;
        ++e;                    // exponent = multiplication count
    }
    uint64_t b = k == q ? p : q;

    // Modular exponentiation with fixed modulus
    // https://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method
    uint64_t r = 1U;
    b %= MOD;
    while (e) {
        if (e & 1U) {
            r = r * b % MOD;
        }
        b = b * b % MOD;
        e >>= 1U;
    }
    return r;
}

static void result(uint64_t p, uint64_t q)
{
    timer();
    uint64_t r = dhke(p, q);
    printf("  %8"PRIu64" %8"PRIu64" : %8"PRIu64"  (%.5f s)\n", p, q, r, timer());

    timer();
    r = dhke(q, p);
    printf("  %8"PRIu64" %8"PRIu64" : %8"PRIu64"  (%.5f s)\n", q, p, r, timer());
}

int main(void)
{
    printf("\nexample\n");
    result(5764801, 17807724);

    printf("\nalgorithm / ednl\n");
    result(15113849, 4206373);

    printf("\nejolson\n");
    result(6270530, 14540258);

    printf("\nlurk101 (1)\n");
    result(16915772, 18447943);

    return 0;
}
