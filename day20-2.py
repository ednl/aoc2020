import numpy as np
from numpy.lib.function_base import place

ids = []
tiles = np.zeros((1,10,10), dtype=np.uint8)  #stub
with open('input20.txt') as f:
    tiledata = f.read().strip().split('\n\n')
    for td in tiledata:
        t = td.strip().split('\n')
        ids.append(int(t[0][5:-1]))
        tile = (np.array([[list(s) for s in t[1:]]]) == '#').astype(np.uint8)
        tiles = np.concatenate((tiles, tile))
tiles = tiles[1:,:,:]  # delete stub

# Original: t,r,b,l (=top,right,bottom,left)
# Rotations: r,-b,l,-t | -b,-l,-t,-r | -l,t,-r,b
# Flipped horizontally: -t,l,-b,r
# Rotations: l,b,r,t | b,-r,t,-l | -r,-t,-l,-b

print(tiles[0])
tiles = np.rot90(tiles, axes=(1, 2))
print(tiles[0])
tiles = np.rot90(tiles, axes=(1, 2))
print(tiles[0])

place = np.zeros((1,1))
# place = np.pad(place, ((1,1),), mode='constant')
