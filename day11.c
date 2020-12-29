#include <stdio.h>   // fopen, fclose, getline
#include <stdlib.h>  // free

#define HOME    "\e[H"
#define CLEAR   "\e[2J"
#define HIDECUR "\e[?25l"

// Test
// #define H 10
// #define W 10
// const char *inp = "input11a.txt";

// Real
#define H 91
#define W 98
const char *inp = "input11.txt";

#define LEN (H * W)
int a[LEN], b[LEN], c[LEN];

void read() {
	FILE *fp;
	char *s = NULL;
	size_t t = 0;
	int i, j, k;

	if ((fp = fopen(inp, "r")) != NULL) {
		i = 0;
		while (getline(&s, &t, fp) > 0) {
			j = 0;
			while (s[j] && s[j] != '\n') {
				k = i * W + j;
				if (k < LEN) {
					a[k] = s[j] == 'L' ? 0 : -1;
				}
				j++;
			}
			i++;
		}
		free(s);
		fclose(fp);
	}
}

void init() {
	int k;
	for (k = 0; k < LEN; ++k) {
		b[k] = a[k];
		c[k] = a[k];
	}
}

int neighbours(int *area, int row, int col, int thresh, int part) {
	int i, j, k, r, c, n = 0;
	for (i = -1; i <= 1; ++i) {
		for (j = -1; j <= 1; ++j) {
			if (i || j) {
				r = row + i;
				c = col + j;
				while (r >= 0 && r < H && c >= 0 && c < W) {
					k = r * W + c;
					if (area[k] != -1 || part == 1) {
						if (area[k] == 1) {
							n++;
							if (n == thresh) {
								return n;
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
	return n;
}

int evolve(int *a1, int *a2, int part) {
	int r, c, k, changed = 0;
	for (r = 0; r < H; ++r) {
		for (c = 0; c < W; ++c) {
			k = r * W + c;
			if (a1[k] == 0) {
				if (neighbours(a1, r, c, 1, part) == 0) {
					a2[k] = 1;
					changed = 1;
				} else {
					a2[k] = 0;
				}
			} else if (a1[k] == 1) {
				if (neighbours(a1, r, c, 3 + part, part) >= 3 + part) {
					a2[k] = 0;
					changed = 1;
				} else {
					a2[k] = 1;
				}
			}
		}
	}
	return changed;
}

void show(int *area) {
	int i, j, k, ch;
	for (i = 0; i < H; ++i) {
		for (j = 0; j < W; ++j) {
			k = i * W + j;
			switch (area[k]) {
				// case  1: ch = '#'; break;
				case  1: printf("##"); break;
				// case -1: ch = ' '; break;
				// case  0: ch = ' '; break;
				// default: ch = ' '; break;
				default: printf("  "); break;
			}
			// printf("%c", ch);
		}
		printf("\n");
	}
	// printf("\n");
}

int occupied(int *area) {
	int k, n = 0;
	for (k = 0; k < LEN; ++k) {
		if (area[k] == 1) {
			n++;
		}
	}
	return n;
}

int main(void)
{
	int part, *p, *q, *t;
	volatile unsigned long count;

	read();
	for (part = 1; part <= 2; ++part) {
		init();
		p = (int *)b;
		q = (int *)c;
		while (evolve(p, q, part)) {
			t = p;
			p = q;
			q = t;
			// printf("%s", CLEAR);
			// printf("%s", HOME);
			// show(p);
			// for (count = 0; count < 20000000; ++count);
		}
		printf("%d\n", occupied(p));
	}

	return 0;
}
