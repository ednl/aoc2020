// Advent of Code 2020, day 11: "Seating System"
// https://adventofcode.com/2020/day/11

#include <stdio.h>   // fopen, fclose, getline
#include <stdlib.h>  // free

// For terminal display
#define HOME    "\e[H"
#define CLEAR   "\e[2J"
#define HIDECUR "\e[?25l"

// Test
// #define H 10
// #define W 10
// const char *inp = "input11a.txt";

// Determine manually from input file
#define H 91
#define W 98
#define LEN (H * W)
const char *inp = "input11.txt";

// Original data and two copies for evolving
// signed because state = -1 | 0 | 1
int data[LEN], area1[LEN], area2[LEN];

// Read and parse the input file
// '.' = floor (-1) never changes
// 'L' = empty seat (0) can become '#' = occupied (1)
void read()
{
	FILE *fp;
	char *s = NULL;
	size_t t = 0;
	int i, j, k;

	if ((fp = fopen(inp, "r")) != NULL) {
		i = 0;  // position in data
		while (getline(&s, &t, fp) > 0) {
			j = 0;  // position in line
			while (s[j] != '\0' && s[j] != '\n') {
				if (i < LEN) {  // shouldn't be necessary if H and W fit the input
					data[i++] = s[j] == 'L' ? 0 : -1;
				}
				j++;
			}
		}
		free(s);
		fclose(fp);
	}
}

// Fresh copies of input data
void init()
{
	for (int i = 0; i < LEN; ++i) {
		area1[i] = area2[i] = data[i];
	}
}

int neighbours(int *area, int row, int col, int thresh, int part)
{
	int i, j, k, r, c, n = 0;
	for (i = -1; i <= 1; ++i) {      // row offset (direction)
		for (j = -1; j <= 1; ++j) {  // col offset (direction)
			if (i || j) {            // not the centre
				r = row + i;         // first row value in this direction
				c = col + j;         // first col value in this direction
				while (r >= 0 && r < H && c >= 0 && c < W) {
					k = r * W + c;   // 1-D array index
					// Part 1 = only direct neighbours, part 2 = 8 lines of sight
					if (area[k] != -1 || part == 1) {
						// Check & stop looking in this direction when reaching a seat
						if (area[k] == 1) {     // occupied?
							n++;                // hididelihi neighborino
							if (n == thresh) {
								return 1;  // reached threshold, no point in counting more
							}
						}
						break;
					}
					r += i;
					c += j;
				}
			}
		}
	}
	return 0;  // did not reach threshold
}

int evolve(int *a1, int *a2, int part)
{
	int r, c, k, changed = 0, thresh = 3 + part;
	for (r = 0; r < H; ++r) {
		for (c = 0; c < W; ++c) {
			k = r * W + c;
			if (a1[k] == 0) {  // empty seat?
				if (neighbours(a1, r, c, 1, part)) {  // any neighbour?
					a2[k] = 0;
				} else {
					a2[k] = 1;  // now it's occupied
					changed = 1;
				}
			} else if (a1[k] == 1) {  // occupied seat?
				if (neighbours(a1, r, c, thresh, part)) {  // at least 4 or 5 neighbours?
					a2[k] = 0;  // now it's empty
					changed = 1;
				} else {
					a2[k] = 1;
				}
			}
		}
	}
	return changed;
}

// Print map of occupied seats on a (large) terminal
void show(int *area)
{
	int i, j, k;
	volatile unsigned long delay;

	printf("%s", CLEAR);
	printf("%s", HOME);
	for (i = 0; i < H; ++i) {
		for (j = 0; j < W; ++j) {
			k = i * W + j;
			printf(area[k] == 1 ? "##" : "  ");
		}
		printf("\n");
	}
	for (delay = 0; delay < 20000000; ++delay);
}

// Total number of occupied seats
int occupied(int *area)
{
	int n = 0;
	for (int i = 0; i < LEN; ++i) {
		if (area[i] == 1) {
			n++;
		}
	}
	return n;
}

int main(void)
{
	int part, *p, *q, *t;

	read();
	for (part = 1; part <= 2; ++part) {
		init();
		p = (int *)area1;
		q = (int *)area2;
		while (evolve(p, q, part)) {
			t = p;
			p = q;
			q = t;
			// show(p);
		}
		// Correct answers for my input: 2303, 2057
		printf("%d\n", occupied(p));
	}

	return 0;
}
