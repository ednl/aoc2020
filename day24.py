from copy import deepcopy

#    0 1 2 3 4 5 6
# 0: x x x x x x x
# 1:  x x x x x x x
# 2: x x x x x x x
# 3:  x x x x x x x
# 4: x x x x x x x
def next(r, c, d):
    if d == 'e':
        return r, c + 1
    if d == 'w':
        return r, c - 1
    dr = -1 if d[0] == 'n' else 1
    dc = r % 2
    if d[1] == 'w':
        dc -= 1
    return r + dr, c + dc

txt = []
with open('input24.txt') as f:
    txt = [line.strip() for line in f]

data = []
i = 0
for s in txt:
    data.append([])
    j = 0
    while j < len(s):
        ch = s[j]
        if ch == 'e' or ch == 'w':
            j += 1
        else:
            ch += s[j + 1]
            j += 2
        data[i].append(ch)
    i += 1

g1 = []
for i in range(301):
    g1.append([0] * 301)

for nav in data:
    r = c = 150
    for bearing in nav:
        r, c = next(r, c, bearing)
    g1[r][c] ^= 1

# 411
print(sum(map(sum, g1)))

def neighbours(grid, r, c):
    odd = r % 2
    n = grid[r][c - 1] + grid[r][c + 1]
    n += grid[r - 1][c + odd - 1] + grid[r - 1][c + odd]
    n += grid[r + 1][c + odd - 1] + grid[r + 1][c + odd]
    return n

g2 = deepcopy(g1)
for _ in range(100):
    for r in range(1, 300):
        for c in range(1, 300):
            nb = neighbours(g1, r, c)
            if g1[r][c]:
                g2[r][c] = 0 if nb == 0 or nb > 2 else 1
            else:
                g2[r][c] = 1 if nb == 2 else 0
    g1, g2 = g2, g1

# 1899 too low
print(sum(map(sum, g1)))
