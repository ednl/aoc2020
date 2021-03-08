#include <iostream>

uint64_t transform(uint64_t s, unsigned l)
{
    uint64_t t(1);
    for (; l ; l--)
        t = t * s % 20201227;
    return t;
}

unsigned loopCount(uint64_t p) {
    uint64_t t(1);
    for (unsigned n(1); ; n++)
        if ((t = t * 7 % 20201227) == p)
            return n;
}

int main() {
    uint64_t pK1 = 16915772, pK2 = 18447943;
    std::cout << transform(pK1, loopCount(pK2)) << std::endl;
    return 0;
}
