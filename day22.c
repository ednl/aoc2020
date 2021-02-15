#include <stdio.h>   // printf
#include <string.h>  // memcpy

// Test
// const unsigned char player1[] = {9, 2, 6, 3, 1};
// const unsigned char player2[] = {5, 8, 4, 7, 10};

// Puzzle
static const unsigned char player1[] = {28, 50, 9, 11, 4, 45, 19, 26, 42, 43, 31, 46, 21, 40, 33, 20, 7, 6, 17, 44, 5, 39, 35, 27, 10};
static const unsigned char player2[] = {18, 16, 29, 41, 14, 12, 30, 37, 36, 24, 48, 38, 47, 34, 15, 8, 49, 23, 1, 3, 32, 25, 22, 13, 2};

static const size_t P1_SIZE = sizeof player1 / sizeof *player1;
static const size_t P2_SIZE = sizeof player2 / sizeof *player2;
static const size_t MAXSIZE = P1_SIZE + P2_SIZE;

typedef unsigned char DECK[MAXSIZE];
typedef struct Game
{
    DECK deck[2];  // two circular buffers
    size_t head[2];
    size_t size[2];
} GAME, *PGAME;

static unsigned int deckid(PGAME pg, size_t player)
{
    unsigned int id = 0;
    size_t head = pg->head[player];
    size_t size = pg->size[player];

    while (size) {
        id += size-- * pg->deck[player][head++];
        if (head == MAXSIZE) {
            head = 0;
        }
    }
    return id;
}

int main(void)
{
    size_t i, winner;
    unsigned int rounds;
    unsigned char card[2];
    GAME game;

    // Init game
    memcpy(game.deck[0], player1, P1_SIZE);
    game.head[0] = 0;
    game.size[0] = P1_SIZE;
    memcpy(game.deck[1], player2, P2_SIZE);
    game.head[1] = 0;
    game.size[1] = P2_SIZE;

    // Play game
    rounds = 0;
    while (game.size[0] && game.size[1]) {

        // Draw 1 card from top of each deck
        for (i = 0; i < 2; ++i) {
            card[i] = game.deck[i][game.head[i]++];
            if (game.head[i] == MAXSIZE) {
                game.head[i] = 0;
            }
            game.size[i]--;
        }

        // Determine round winner from card values
        // true = 1 = player 1 wins, false = 0 = player 0 wins
        winner = card[1] > card[0];

        // Move 2 cards to bottom of winner's deck, highest first
        for (i = 0; i < 2; ++i) {
            game.deck[winner][(game.head[winner] + game.size[winner]++) % MAXSIZE] = card[(winner + i) % 2];
        }

        ++rounds;
    }

    // Determine game winner from deck size
    // true = 1 = player 1 wins, false = 0 = player 0 wins
    winner = game.size[0] == 0;
    printf("%zu %u %u\n", winner, rounds, deckid(&game, winner));

    return 0;
}
