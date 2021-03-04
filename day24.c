#include <stdio.h>   // getline
#include <stdlib.h>  // malloc, free
#include <string.h>  // memset

// Puzzle input file name
static const char *inp = "input24.txt";
static const int turns = 100;

// Hexagonal grid, max size to be determined
static unsigned char *grid = NULL;
static int midpoint = 0, width = 0, gridsize = 0;

static int maxlinelen(void)
{
    FILE *fp = NULL;
    char *s = NULL;
    size_t t = 0;
    int maxlen = 0, n;

    // Count lines, determine max line length
    if ((fp = fopen(inp, "r")) != NULL) {
        while ((n = (int)getline(&s, &t, fp)) > 0) {
            if (n > maxlen) {
                maxlen = n;  // includes delimiter
            }
        }
        free(s);
        fclose(fp);
    }
    return maxlen;
}

static int counttiles(void)
{
    int i, n = 0;

    for (i = 0; i < gridsize; ++i) {
        n += grid[i];
    }
    return n;
}

static int ix(int x, int y)
{
    return width * y + x;
}

static void part1(void)
{
    FILE *fp = NULL;
    char *s = NULL, *c;
    size_t t = 0;
    int q, r;

    if ((fp = fopen(inp, "r")) != NULL) {
        while (getline(&s, &t, fp) > 0) {
            c = s;
            q = r = midpoint;  // axial coordinates, start in middle
            while (*c != '\n' && *c != '\0') {
                if (*c == 'e') {
                    ++q;
                } else if (*c == 'w') {
                    --q;
                } else if (*c == 'n') {
                    --r;
                    if (*(++c) == 'e') {
                        ++q;
                    }
                } else if (*c == 's') {
                    ++r;
                    if (*(++c) == 'w') {
                        --q;
                    }
                }
                ++c;
            }
            grid[ix(q, r)] ^= 1;
        }
        free(s);
        fclose(fp);
    }
}

static unsigned char neighbours(unsigned char *a, int x, int y)
{
    unsigned char n = 0;

    n += a[ix(x + 1, y    )];  // E
    n += a[ix(x - 1, y    )];  // W
    n += a[ix(x + 1, y - 1)];  // NE
    n += a[ix(x    , y - 1)];  // NW
    n += a[ix(x    , y + 1)];  // SE
    n += a[ix(x - 1, y + 1)];  // SW
    return n;
}

static void part2(void)
{
    int x, y, i, j;
    unsigned char t, n, *grid2, *a, *b, *tmp;

    grid2 = malloc((size_t)gridsize * sizeof *grid);
    memset(grid2, 0, gridsize);
    a = grid;
    b = grid2;
    for (i = turns; i >= 1; --i) {
        // Use turn counter as grid reach limiter
        for (y = i; y < width - i; ++y) {
            for (x = i; x < width - i; ++x) {
                j = ix(x, y);
                t = a[j];
                n = neighbours(a, x, y);
                if (t == 0 && n == 2) {
                    b[j] = 1;
                } else if (t == 1 && (n == 0 || n > 2)) {
                    b[j] = 0;
                } else {
                    b[j] = t;
                }
            }
        }
        tmp = a;
        a = b;
        b = tmp;
    }
    free(grid2);
}

int main(void)
{
    // Get line length, add turns => max grid size
    midpoint = maxlinelen() + turns;  // mid point
    width = midpoint * 2 - 1;         // width and height of the grid
    gridsize = width * width;         // array length
    grid = malloc((size_t)gridsize * sizeof *grid);
    memset(grid, 0, gridsize);

    part1();
    printf("Part 1: %d\n", counttiles());

    part2();
    printf("Part 2: %d\n", counttiles());

    free(grid);
    return 0;
}
