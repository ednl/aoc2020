#include <stdio.h>
#include <stdlib.h>

const size_t TURNS = 30000000;
unsigned int seen[TURNS];

const unsigned int game[] = {13, 16, 0, 12, 15, 1};
const size_t gamesize = sizeof game / sizeof(unsigned int);

int main(void)
{
	unsigned int i, j, lastnum = game[gamesize - 1];

	for (i = 0; i < TURNS; ++i) {
		seen[i] = 0;
	}

	i = 1;
	while (i < gamesize) {
		seen[game[i - 1]] = i;
		++i;
	}

	while (i < TURNS) {
		j = seen[lastnum];
		seen[lastnum] = i;
		lastnum = j ? i - j : 0;
		++i;
	}

	printf("%u\n", lastnum);
	return 0;
}
