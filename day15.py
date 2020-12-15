# Van Eck Missing Number
# https://www.rosettacode.org/wiki/Van_Eck_sequence
def play(game, turns):
    seen = [0] * turns  # dumb but fast :(
    lastnum = game[-1]
    i = 0
    while i < len(game):
        seen[game[i - 1]] = i
        i += 1
    while i < turns:
        j = seen[lastnum]
        seen[lastnum] = i
        lastnum = 0 if j == 0 else i - j
        i += 1
    return lastnum

# Part 1
game = [0,3,6]
print(play(game, 2020))

# Part 2
game = [13,16,0,12,15,1]
print(play(game, 30000000))
