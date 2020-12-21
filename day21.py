possible = {}
ingredients = {}
with open('input21.txt') as f:
    for line in f:
        ingr, allerg = line.split(' (contains ')
        ingr = set(ingr.split())
        for i in ingr:
            ingredients[i] = ingredients.get(i, 0) + 1
        for a in allerg[:-2].split(', '):
            if a in possible:
                possible[a] &= ingr
            else:
                possible[a] = ingr.copy()

danger = {}
while len(possible):
    allergen = [a for a, i in possible.items() if len(i) == 1][0]
    ingr = possible.pop(allergen)
    for a, i in possible.items():
        i -= i & ingr
    danger[allergen] = ingr.pop()

# Part 1
print(sum([c for i, c in ingredients.items() if i not in danger.values()]))

# Part 2
print(','.join([i for _, i in sorted([(a, i) for a, i in danger.items()])]))
