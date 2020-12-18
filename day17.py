import numpy as np
from scipy.signal import convolve

with open('input17.txt') as f:
    data = (np.array([list(i.strip()) for i in f]) == '#').astype(np.uint8)

def cycle(init, dim, gen=6):
    state = init.reshape([1] * (dim - init.ndim) + list(init.shape))
    kernel = np.ones([3] * dim, dtype=np.uint8)
    for _ in range(gen):
        nb = convolve(state, kernel)
        state = np.pad(state, ((1,1),), mode='constant') & (nb == 4) | (nb == 3)
    return np.sum(state)

# Part 1
print(cycle(data, 3))

# Part 2
print(cycle(data, 4))
