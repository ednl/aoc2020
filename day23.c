#include <stdio.h>
#include <stdlib.h>

// #define CUPS         9u
// #define MOVES      100u
#define CUPS   1000000u
#define MOVES 10000000u
#define PICK         3u
#define LABELS       9u

unsigned int a[CUPS + 1];
unsigned int b[LABELS] = {3, 6, 2, 9, 8, 1, 7, 5, 4};

int main(void)
{
    unsigned int i, j, cur, move, nxt, found;

    for (i = 0; i <= CUPS; ++i) {
        a[i] = i + 1u;
    }

    a[0] = a[CUPS] = b[0];
    for (i = 0; i < LABELS - 1; ++i) {
        a[b[i]] = b[i + 1];
    }
    a[b[LABELS - 1]] = CUPS == LABELS ? b[0] : LABELS + 1;

    cur = 0;
    move = MOVES;
    while (move--) {
        cur = a[cur];
        nxt = cur != 1 ? cur - 1 : CUPS;

        do {
            i = cur;
            found = 0;
            for (j = 0; j < PICK; ++j) {
                if ((i = a[i]) == nxt) {
                    found = 1;
                    nxt = nxt != 1 ? nxt - 1 : CUPS;
                    break;
                }
            }
        } while (found);

        j = a[i];
        a[i] = a[nxt];
        a[nxt] = a[cur];
        a[cur] = j;
    }

    if (CUPS < 10) {
        i = a[1];
        while (i != 1) {
            printf("%u", i);
            i = a[i];
        }
        printf("\n");
    } else {
        printf("%lu\n", (unsigned long)a[1] * a[a[1]]);
    }

    return 0;
}
