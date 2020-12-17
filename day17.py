import numpy as np
from scipy.signal import convolve

with open('input17.txt') as f:
    data = np.array([list(map(lambda x: 1 if x == '#' else 0, line.strip())) for line in f], dtype=np.uint8)

def cycle(init, dim, gen=6):
    grid = init.reshape([1] * (dim - len(init.shape)) + list(init.shape))
    kernel = np.ones([3] * dim, dtype=np.uint8)
    for i in range(gen):
        nb = convolve(grid, kernel)
        grid = np.pad(grid, ((1, 1),), mode='constant')
        grid = ((nb == 3) | ((grid == 1) & (nb == 4))).astype(np.uint8)
    return np.sum(grid)

# Part 1
print(cycle(data, 3))

# Part 2
print(cycle(data, 4))
