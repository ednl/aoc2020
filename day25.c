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
#include <stdint.h>    // uint64_t
#include <inttypes.h>  // PRIu64
#include <stdbool.h>   // bool, true, false
#include <time.h>      // clock_gettime

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

int main(void)
{
    timer();
    uint64_t e = 0, r = 1, k = 1, b = 7, m = 20201227, p = 15113849, q = 4206373;

    while (k != p && k != q) {  // symmetry in p,q
        k = k * b % m;
        ++e;  // count multiplications = exponent
    }
    b = k == q ? p : q;  // new base for second phase

    // Modular exponentiation r = modpow(b,e,m)
    // https://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method
    b %= m;
    while (e) {
        if (e & 1U) {
            r = r * b % m;
        }
        e >>= 1U;
        b = b * b % m;
    }

    printf("%"PRIu64" %.5f\n", r, timer());
    return 0;
}
