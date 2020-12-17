import numpy as np
from scipy.signal import convolve

with open('input17.txt') as f:
    data = np.array([list(map(lambda x: 1 if x == '#' else 0, line.strip())) for line in f], dtype=np.uint8)

def cycle(init, dim, gen=6):
    s = init.shape
    grid = init.reshape([1] * (dim - len(s)) + list(s))
    kernel = np.ones([3] * dim, dtype=np.uint8)
    kernel[(1,) * dim] = 0
    for i in range(gen):
        nb = convolve(grid, kernel)
        grid = np.pad(grid, ((1, 1),), mode='constant')
        next = (((grid == 1) & (nb > 1) & (nb < 4)) | ((grid == 0) & (nb == 3))).astype(np.uint8)
        grid = next
    return np.sum(grid)

# Part 1
print(cycle(data, 3))

# Part 2
print(cycle(data, 4))
