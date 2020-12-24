from copy import deepcopy

#    0 1 2 3 4 5 6
# 0: x x x x x x x
# 1:  x x x x x x x
# 2: x x x x x x x
# 3:  x x x x x x x
# 4: x x x x x x x

# evenkernel = [
#     [1, 1, 0],
#     [1, 0, 1],
#     [1, 1, 0]
# ]
# oddkernel = [
#     [0, 1, 1],
#     [1, 0, 1],
#     [0, 1, 1]
# ]

step = [{
    # step from even row
    'e' : ( 0,  1),
    'w' : ( 0, -1),
    'ne': (-1,  0),
    'nw': (-1, -1),
    'se': ( 1,  0),
    'sw': ( 1, -1),
},
{
    # step from odd row
    'e' : ( 0,  1),
    'w' : ( 0, -1),
    'ne': (-1,  1),
    'nw': (-1,  0),
    'se': ( 1,  1),
    'sw': ( 1,  0),
}]

def next(r, c, id):
    dr, dc = step[r % 2][id]
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

generations = 100
maxdist = max(map(len, data))
dim = 2 * (maxdist + generations) + 3
mid = dim // 2

g1 = []
for i in range(dim):
    g1.append([0] * dim)

for nav in data:
    r = c = mid
    for bearing in nav:
        r, c = next(r, c, bearing)
    g1[r][c] ^= 1

# Part 1 = 411
print(sum(map(sum, g1)))

def neighbours(grid, r, c):
    odd = r % 2
    n = grid[r][c - 1] + grid[r][c + 1]
    n += grid[r - 1][c + odd - 1] + grid[r - 1][c + odd]
    n += grid[r + 1][c + odd - 1] + grid[r + 1][c + odd]
    return n

g2 = deepcopy(g1)
for gen in range(generations):
    for r in range(mid - maxdist - gen, mid + maxdist + gen):
        for c in range(mid - maxdist - gen, mid + maxdist + gen):
            nb = neighbours(g1, r, c)
            if g1[r][c]:
                g2[r][c] = 0 if nb == 0 or nb > 2 else 1
            else:
                g2[r][c] = 1 if nb == 2 else 0
    g1, g2 = g2, g1

# Part 2 = 4092
print(sum(map(sum, g1)))
