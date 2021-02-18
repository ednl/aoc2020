#include <stdio.h>   // printf, fopen, fclose, getline
#include <stdlib.h>  // free
#include <time.h>    // clock, difftime

#define PLAYERS 2

// Test
// const unsigned char player1[] = {9, 2, 6, 3, 1};
// const unsigned char player2[] = {5, 8, 4, 7, 10};

#ifdef RPPICO
// Puzzle
static const unsigned char player1[] = {28, 50, 9, 11, 4, 45, 19, 26, 42, 43, 31, 46, 21, 40, 33, 20, 7, 6, 17, 44, 5, 39, 35, 27, 10};
static const unsigned char player2[] = {18, 16, 29, 41, 14, 12, 30, 37, 36, 24, 48, 38, 47, 34, 15, 8, 49, 23, 1, 3, 32, 25, 22, 13, 2};
// Yes, compiler, these *are* constant
static const size_t P1_SIZE = sizeof player1 / sizeof *player1;
static const size_t P2_SIZE = sizeof player2 / sizeof *player2;
static const size_t MAXHAND = P1_SIZE + P2_SIZE;
#else
#define MAXHAND 50
static const char *inp = "input22.txt";
#endif

// A hand is a stack of cards + index to the first card + size of the stack
typedef struct {
    unsigned int size, head;
    unsigned char card[MAXHAND];
} HAND, *PHAND;

// Each player has a hand
static HAND player[PLAYERS];

static void read()
{
	FILE *fp;
	char *s = NULL;
	size_t t = 0;
	unsigned int i = 0, j = 0;
    int k;

	if ((fp = fopen(inp, "r")) != NULL) {
		while (getline(&s, &t, fp) > 0 && i < PLAYERS) {
            if (s[0] == 'P') {
                player[i].size = 0;
                player[i].head = 0;
            } else if (s[0] == '\n') {
                player[i++].size = j;
                j = 0;
            } else if (j < MAXHAND) {
                k = atoi(s);
                if (k > 0 && k <= 255) {
                    player[i].card[j++] = (unsigned char)k;
                }
            }
		}
        if (i < PLAYERS && j > player[i].size) {
            player[i].size = j;
        }
		free(s);
		fclose(fp);
	}
}

static void show()
{
    unsigned int i, j, k;

    for (i = 0; i < PLAYERS; ++i) {
        printf("Player %i:", i + 1);
        k = player[i].head;
        for (j = 0; j < player[i].size; ++j) {
            printf(" %u", player[i].card[k++]);
            if (k == MAXHAND) {
                k = 0;
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Score of a deck (also a fairly good state identifier)
// calculate from bottom: 1 * value1 + 2 * value2 + 3 * value3 + ... + size * valueSize
static unsigned int score(PHAND ph)
{
    unsigned int id = 0, size = ph->size, head = ph->head;

    while (size) {
        id += size-- * ph->card[head++];
        if (head == MAXHAND) {
            head = 0;
        }
    }
    return id;
}

int main()
{
    unsigned int i, win, rounds, res;
    unsigned char draw[PLAYERS];
    struct timespec t0, t1;
    double dt;

    // Start stopwatch
    clock_gettime(CLOCK_MONOTONIC, &t0);

    read();
    show();

    // Part 1
    rounds = 0;
    while (player[0].size && player[1].size) {

        // Draw 1 card each
        for (i = 0; i < PLAYERS; ++i) {
            draw[i] = player[i].card[player[i].head++];
            if (player[i].head == MAXHAND) {
                player[i].head = 0;
            }
            player[i].size--;
        }

        // Determine round winner from card values
        // true = 1 = player 1 wins, false = 0 = player 0 wins
        win = draw[1] > draw[0];

        // Move 2 cards to bottom of winner's hand, highest first
        for (i = 0; i < PLAYERS; ++i) {
            player[win].card[(player[win].head + player[win].size++) % MAXHAND] = draw[(win + i) % PLAYERS];
        }

        ++rounds;
    }

    // Determine game winner from hand size
    // true = 1 = player 1 wins, false = 0 = player 0 wins
    win = player[0].size == 0;
    res = score(&player[win]);

    // Stop stopwatch
    clock_gettime(CLOCK_MONOTONIC, &t1);
    dt = 1.0 * t1.tv_sec + 1e-9 * t1.tv_nsec - (1.0 * t0.tv_sec + 1e-9 * t0.tv_nsec);

    printf("winner: %u\nrounds: %u\nscore : %u\ntime  : %.6f s\n", win + 1, rounds, res, dt);
    return 0;
}
