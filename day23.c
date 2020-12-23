#include <stdio.h>

#define CUPS    1000000u
#define MOVES  10000000u
#define LABELS        9u

unsigned int next[CUPS + 1];
unsigned int cups[LABELS] = {3, 6, 2, 9, 8, 1, 7, 5, 4};

int main(void)
{
    unsigned int i, j, cur, moves, ins, p1, p2, p3;

    for (i = 1; i < CUPS; ++i) {
        next[i] = i + 1u;
    }
    next[0] = next[CUPS] = cups[0];

    for (i = 0; i < LABELS - 1; ++i) {
        next[cups[i]] = cups[i + 1];
    }
    next[cups[LABELS - 1]] = CUPS == LABELS ? cups[0] : LABELS + 1;

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
        j = next[p1];
        next[p1] = next[ins];
        next[ins] = next[cur];
        next[cur] = j;
    }

    if (CUPS < 10) {
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
