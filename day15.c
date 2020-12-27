#include <stdio.h>

#define TURNS 30000000u
unsigned int seen[TURNS] = {0};

const unsigned int game[] = {13, 16, 0, 12, 15, 1};
const size_t gamesize = sizeof game / sizeof(unsigned int);

int main(void)
{
	unsigned int i, j, lastnum = game[gamesize - 1];

	for (i = 1; i < gamesize; ++i) {
		seen[game[i - 1]] = i;
	}
	for (; i < TURNS; ++i) {
		j = seen[lastnum];
		seen[lastnum] = i;
		lastnum = j ? i - j : 0;
	}

	printf("%u\n", lastnum);
	return 0;
}
