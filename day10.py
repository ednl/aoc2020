from collections import Counter

with open('input10.txt') as f:
	a = sorted([int(line) for line in f])

a.append(a[-1] + 3)
a.insert(0, 0)
d = [a[i + 1] - a[i] for i in range(len(a) - 1)]

# Part 1
c = Counter(d)
print(c[1] * c[3])

# Part 2
streak = []
len = 0
for i in d:
	if i == 1:
		len += 1
	else:
		if len > 1:
			streak.append(len)
		len = 0

# Pairs of (k,v) where
#   v = number of ways of summing up to k
#   using any numbers from (1,2,3)
#   where different order counts as a different way
comb = {2: 2, 3: 4, 4: 7, 5: 13}

p = 1
for i in streak:
	p *= comb[i]

print(p)
