#include <stdio.h>     // printf
#include <stdint.h>    // uint32_t, UINT32_C, uint64_t, UINT64_C
#include <inttypes.h>  // PRIu32, PRIu64

#define LABELS  (UINT32_C(9))
#define CUPS    (UINT32_C(1000000))
#define MOVES   (UINT32_C(10000000))

static const uint_fast32_t init[LABELS] = {3, 6, 2, 9, 8, 1, 7, 5, 4};  // puzzle input
static uint_fast32_t next[CUPS + 1];

int main(void)
{
    uint_fast32_t i, j, cur, moves, ins, p1, p2, p3;

    for (i = 1; i < CUPS; ++i) {
        next[i] = i + 1;
    }
    next[0] = next[CUPS] = init[0];

    for (i = 0; i < LABELS - 1; ++i) {
        next[init[i]] = init[i + 1];
    }
    next[init[LABELS - 1]] = CUPS == LABELS ? init[0] : LABELS + 1;

    cur = 0;
    moves = MOVES;
    while (moves--) {
        cur = next[cur];
        ins = cur - 1;
        if (!ins)
            ins = CUPS;
        p1 = next[cur];
        p2 = next[p1];
        p3 = next[p2];
        while (ins == p1 || ins == p2 || ins == p3) {
            --ins;
            if (!ins)
                ins = CUPS;
        }
        j = next[p3];
        next[p3] = next[ins];
        next[ins] = next[cur];
        next[cur] = j;
    }

    if (CUPS < 10) {
        i = next[1];
        while (i != 1) {
            printf("%"PRIuFAST32, i);
            i = next[i];
        }
        printf("\n");
    } else {
        printf("%"PRIu64"\n", (uint64_t)next[1] * next[next[1]]);
    }

    return 0;
}
