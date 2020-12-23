#include <stdio.h>

#define CUPCOUNT  1000000u
#define MOVES    10000000u
#define PICK            3u
#define LABELS          9u

unsigned int next[CUPCOUNT + 1];
unsigned int cups[LABELS] = {3, 6, 2, 9, 8, 1, 7, 5, 4};

int main(void)
{
    unsigned int i, j, cur, movecount, ins, p1, p2, p3;

    for (i = 1; i < CUPCOUNT; ++i) {
        next[i] = i + 1u;
    }
    next[0] = next[CUPCOUNT] = cups[0];

    for (i = 0; i < LABELS - 1; ++i) {
        next[cups[i]] = cups[i + 1];
    }
    next[cups[LABELS - 1]] = CUPCOUNT == LABELS ? cups[0] : LABELS + 1;

    cur = 0;
    movecount = MOVES;
    while (movecount--) {
        cur = next[cur];
        ins = cur - 1;
        if (!ins)
            ins = CUPCOUNT;
        p1 = next[cur];
        p2 = next[p1];
        p3 = next[p2];
        while (ins == p1 || ins == p2 || ins == p3) {
            --ins;
            if (!ins)
                ins = CUPCOUNT;
        }
        j = next[p1];
        next[p1] = next[ins];
        next[ins] = next[cur];
        next[cur] = j;
    }

    if (CUPCOUNT < 10) {
        i = next[1];
        while (i != 1) {
            printf("%u", i);
            i = next[i];
        }
        printf("\n");
    } else {
        printf("%lu\n", (unsigned long)next[1] * next[next[1]]);
    }

    return 0;
}
