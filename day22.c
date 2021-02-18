#include <stdio.h>   // printf, fopen, fclose, getline
#include <stdlib.h>  // free
#include <stdint.h>  // uint32_t
#include <time.h>    // clock, difftime

#define PLAYERS 2
#define MAXHAND 50
#define SET_INC 64
static const char *inp = "input22.txt";
// static const unsigned char player1[] = {28, 50, 9, 11, 4, 45, 19, 26, 42, 43, 31, 46, 21, 40, 33, 20, 7, 6, 17, 44, 5, 39, 35, 27, 10};
// static const unsigned char player2[] = {18, 16, 29, 41, 14, 12, 30, 37, 36, 24, 48, 38, 47, 34, 15, 8, 49, 23, 1, 3, 32, 25, 22, 13, 2};
// static const size_t P1_SIZE = sizeof player1 / sizeof *player1;
// static const size_t P2_SIZE = sizeof player2 / sizeof *player2;

typedef struct {
    unsigned int size, head;
    unsigned char card[MAXHAND];
} HAND, *PHAND;

typedef uint32_t setdata_t;
typedef struct {
    unsigned int len, maxlen;
    setdata_t *data;
} SET, *PSET;

static unsigned int set_init(PSET s)
{
    s->len = 0;
    s->maxlen = SET_INC;
    size_t size = s->maxlen * sizeof(setdata_t);
    void *res = s->data == NULL ? malloc(size) : realloc(s->data, size);
    if (res) {
        s->data = (setdata_t*)res;
        return 1;  // success
    }
    // Failure
    if (s->data) {
        free(s->data);
        s->data = NULL;
    }
    s->maxlen = 0;
    return 0;
}

static unsigned int set_add(PSET s, setdata_t val)
{
    unsigned int i, ins = s->len;

    // Determine insertion point
    while (ins > 0 && s->data[ins - 1] > val) {
        --ins;
    }
    // Already in set?
    if (ins > 0 && s->data[ins - 1] == val) {
        return 0;
    }
    // Grow if needed
    if (s->len == s->maxlen) {
        s->maxlen += SET_INC;
        size_t size = s->maxlen * sizeof(setdata_t);
        void *res = s->data ? realloc(s->data, size) : malloc(size);
        if (res) {
            s->data = (setdata_t*)res;
        } else {
            // No room in the inn
            s->maxlen -= SET_INC;
            return 0;
        }
    }
    // Shift larger values
    for (i = s->len; i > ins; --i) {
        s->data[i] = s->data[i - 1];
    }
    // Insert new value
    s->data[ins] = val;
    s->len++;
    return 1;
}

static void set_clean(PSET s)
{
    if (s->data) {
        free(s->data);
        s->data = NULL;
    }
    s->len = 0;
    s->maxlen = 0;
}

static double timer(void)
{
    static unsigned int start = 1;
    static struct timespec t0;
    struct timespec t1;

    if (start) {
        start = 0;
        clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        return 0;
    } else {
        clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        start = 1;
        return 1.0 * t1.tv_sec + 1e-9 * t1.tv_nsec - (1.0 * t0.tv_sec + 1e-9 * t0.tv_nsec);
    }
}
static void read(PHAND p)
{
	FILE *fp;
	char *s = NULL;
	size_t t = 0;
	unsigned int i = 0, j = 0;
    int k;

	if ((fp = fopen(inp, "r")) != NULL) {
		while (getline(&s, &t, fp) > 0 && i < PLAYERS) {
            if (s[0] == 'P') {
                p[i].size = 0;
                p[i].head = 0;
            } else if (s[0] == '\n') {
                p[i++].size = j;
                j = 0;
            } else if (j < MAXHAND) {
                k = atoi(s);
                if (k > 0 && k <= 255) {
                    p[i].card[j++] = (unsigned char)k;
                }
            }
		}
        if (i < PLAYERS && j > p[i].size) {
            p[i].size = j;
        }
		free(s);
		fclose(fp);
	}
}

static void show(PHAND p)
{
    unsigned int i, j, k;

    for (i = 0; i < PLAYERS; ++i) {
        printf("Player %i:", i + 1);
        k = p[i].head;
        for (j = 0; j < p[i].size; ++j) {
            printf(" %u", p[i].card[k++]);
            if (k == MAXHAND) {
                k = 0;
            }
        }
        printf("\n");
    }
    printf("\n");
}

static uint32_t score(PHAND p)
{
    uint32_t id = 0;
    unsigned int size = p->size, head = p->head;

    while (size) {
        id += size-- * p->card[head++];
        if (head == MAXHAND) {
            head = 0;
        }
    }
    return id;
}

static uint32_t gameid(PHAND p)
{
    // Unique enough (max = sum(squares(1..50)) = 42925 and 1<<16 = 65536)
    return (score(p) << 16) | score(&p[1]);
}

static unsigned int game1(PHAND p)
{
    unsigned int i, win;
    unsigned char draw[PLAYERS];

    while (p[0].size && p[1].size) {

        for (i = 0; i < PLAYERS; ++i) {
            draw[i] = p[i].card[p[i].head++];
            if (p[i].head == MAXHAND) {
                p[i].head = 0;
            }
            p[i].size--;
        }
        win = draw[1] > draw[0];

        for (i = 0; i < PLAYERS; ++i) {
            p[win].card[(p[win].head + p[win].size++) % MAXHAND] = draw[(win + i) % PLAYERS];
        }
    }

    return p[1].size > p[0].size;
}

// static unsigned int player1wins(PHAND p)
// {
//     unsigned int i, j, k, n, max[PLAYERS];

//     for (i = 0; i < PLAYERS; ++i) {
//         max[i] = 0;
//         k = p[i].head;
//         for (j = 0; j < p[i].size; ++j) {
//             n = p[i].card[k++];
//             if (k == MAXHAND) {
//                 k = 0;
//             }
//             if (n > max[i]) {
//                 max[i] = n;
//             }
//         }
//     }
//     return max[0] > max[1];
// }

static unsigned int game2(PHAND p, unsigned int level)
{
    unsigned int i, j, k, win;
    unsigned char draw[PLAYERS];
    SET uid = {.len = 0, .maxlen = 0, .data = NULL};
    HAND subgame[2];

    set_init(&uid);
    while (p[0].size && p[1].size) {

        // Duplicate game? (or set can't be expanded)
        if (!set_add(&uid, gameid(p))) {
            set_clean(&uid);
            return 0;  // player 1 wins
        }

        // Draw 1 card each
        for (i = 0; i < PLAYERS; ++i) {
            draw[i] = p[i].card[p[i].head++];
            if (p[i].head == MAXHAND) {
                p[i].head = 0;
            }
            p[i].size--;
        }

        // At least as many cards left as value drawn?
        if (p[0].size >= draw[0] && p[1].size >= draw[1]) {
            // Copy hands to subgame
            for (i = 0; i < PLAYERS; ++i) {
                subgame[i].size = draw[i];
                subgame[i].head = 0;
                k = p[i].head;
                for (j = 0; j < draw[i]; ++j) {
                    subgame[i].card[j] = p[i].card[k++];
                    if (k == MAXHAND) {
                        k = 0;
                    }
                }
            }
            // And recurse
            win = game2(subgame, level + 1);
        } else {
            win = draw[1] > draw[0];
        }

        for (i = 0; i < PLAYERS; ++i) {
            p[win].card[(p[win].head + p[win].size++) % MAXHAND] = draw[(win + i) % PLAYERS];
        }
    }
    set_clean(&uid);
    return p[1].size > p[0].size;
}

int main(void)
{
    HAND player[PLAYERS];
    unsigned int win, res;

    timer();

    // Part 1
    read(player);
    show(player);
    win = game1(player);
    res = score(&player[win]);
    printf("Part 1\nwinner : %u\ntarget : 31629\nscore  : %u\n\n", win + 1, res);

    // Part 2
    read(player);
    win = game2(player, 0);
    res = score(&player[win]);
    printf("Part 2\nwinner : %u\ntarget : 35196\nscore  : %u\n\n", win + 1, res);

    printf("time  : %.6f s\n", timer());
    return 0;
}
