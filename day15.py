def lastnum(game, turns):
    prev = {}
    for i in range(len(game) - 1):
        prev[game[i]] = i

    i = len(game) - 1
    latest = game[i]

    while i < turns - 1:
        next = i - prev.get(latest, i)
        prev[latest] = i
        latest = next
        i += 1

    return latest

# Part 1
game = [0,3,6]
print(lastnum(game, 2020))

# Part 2
game = [13,16,0,12,15,1]
print(lastnum(game, 30000000))
