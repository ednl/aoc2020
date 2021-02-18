#include <stdio.h>   // printf, fopen, fclose, getline
#include <stdlib.h>  // free
#include <time.h>    // clock, difftime

#define PLAYERS 2
#define MAXHAND 50
static const char *inp = "input22.txt";
// static const unsigned char player1[] = {28, 50, 9, 11, 4, 45, 19, 26, 42, 43, 31, 46, 21, 40, 33, 20, 7, 6, 17, 44, 5, 39, 35, 27, 10};
// static const unsigned char player2[] = {18, 16, 29, 41, 14, 12, 30, 37, 36, 24, 48, 38, 47, 34, 15, 8, 49, 23, 1, 3, 32, 25, 22, 13, 2};
// static const size_t P1_SIZE = sizeof player1 / sizeof *player1;
// static const size_t P2_SIZE = sizeof player2 / sizeof *player2;

typedef struct {
    unsigned int size, head;
    unsigned char card[MAXHAND];
} HAND, *PHAND;

static double timer(void)
{
    static unsigned int start = 1;
    static struct timespec t0;
    struct timespec t1;

    if (start) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        start = 0;
        return 0;
    } else {
        clock_gettime(CLOCK_MONOTONIC, &t1);
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

static unsigned int score(PHAND p)
{
    unsigned int id = 0, size = p->size, head = p->head;

    while (size) {
        id += size-- * p->card[head++];
        if (head == MAXHAND) {
            head = 0;
        }
    }
    return id;
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

int main(void)
{
    HAND player[PLAYERS];
    unsigned int win, res;

    // Part 1
    timer();
    read(player);
    show(player);
    win = game1(player);
    res = score(&player[win]);
    printf("winner: %u\nscore : %u\ntime  : %.6f s\n", win + 1, res, timer());

    return 0;
}
