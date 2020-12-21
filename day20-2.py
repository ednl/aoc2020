import numpy as np

ids = []
tiles = np.zeros((1,10,10), dtype=np.uint8)  #stub
with open('input20.txt') as f:
    tiledata = f.read().strip().split('\n\n')
    for td in tiledata:
        t = td.strip().split('\n')
        ids.append(int(t[0][5:-1]))
        tile = (np.array([[list(s) for s in t[1:]]]) == '#').astype(np.uint8)
        tiles = np.concatenate((tiles, tile))
tiles = np.delete(tiles, 0, axis=0)  # delete stub

# tiles = np.rot90(tiles, axes=(1, 2))
# tiles = np.fliplr(tiles)
