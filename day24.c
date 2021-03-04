#include <stdio.h>   // getline
#include <stdlib.h>

static const char *inp = "input24.txt";
static const int axq[] = {1, 1, 0, -1, -1, 0};
static const int axr[] = {0, -1, -1, 0, 1, 1};

static int part1(void)
{
    FILE *fp = NULL;
    char *s = NULL, *c;
    size_t t = 0;
    int n = 0, q, r;

    // Determine max
    if ((fp = fopen(inp, "r")) != NULL) {
        while (getline(&s, &t, fp) > 0) {
            q = r = 0;
            c = s;
            while (*c != '\n' && *c != '\r' && *c != '\0') {
                if (*c == 'e') {
                    q += axq[0];
                    r += axr[0];
                } else if (*c == 'w') {
                    q += axq[3];
                    r += axr[3];
                } else if (*c == 'n') {
                    ++c;
                    if (*c == 'e') {
                        q += axq[1];
                        r += axr[1];
                    } else if (*c == 'w') {
                        q += axq[2];
                        r += axr[2];
                    }
                } else if (*c == 's') {
                    ++c;
                    if (*c == 'e') {
                        q += axq[5];
                        r += axr[5];
                    } else if (*c == 'w') {
                        q += axq[4];
                        r += axr[4];
                    }
                }
                ++c;
            }
            printf("%3d %3d %3d\n", n, q, r);
            ++n;
        }
        free(s);
        fclose(fp);
    }
    return n;
}

int main(void)
{
    part1();
    return 0;
}
