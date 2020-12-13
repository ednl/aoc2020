from math import prod

with open('input13.txt') as f:
	# First line = my earliest departure time
	leave = int(f.readline())
	# Second line = bus service where number = bus ID
	sched = list(map(lambda x: 0 if x == 'x' else int(x), f.readline().rstrip('\n').split(',')))

# When does this bus leave? (counting from time = 0..bus-1)
def nextdeparture(time, bus):
	return (bus - (time % bus)) % bus

# Part 1 ############################################################

# Only look at buses in service
buses = list(filter(lambda x: x > 0, sched))

# How long do I have to wait for each bus?
wait = [nextdeparture(leave, bus) for bus in buses]

# Sort by departure time
table = sorted(zip(wait, buses))

# Catch the first bus
minutes, firstbus = table[0]
print(minutes * firstbus)

# Part 2 ############################################################

# Extended Euclidian algorithm
#   return: Bézout's coefficients and GCD
# https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
# https://en.wikipedia.org/wiki/Bézout%27s_identity
def ext_gcd(a, b):
	r0, r1 = a, b
	s0, s1 = 1, 0
	while r1:
		q = r0 // r1
		r0, r1 = r1, r0 - q * r1
		s0, s1 = s1, s0 - q * s1
	t = 0 if b == 0 else (r0 - s0 * a) // b
	return s0, t, r0

# First add indices (=time + i from the problem) to bus IDs
table = list(zip(range(len(sched)), sched))

# Then keep only buses in service
table = list(filter(lambda x: x[1] > 0, table))

# Transform each index to departure time
table = list(map(lambda x: (nextdeparture(x[0], x[1]), x[1]), table))

# Product of all bus IDs
p = prod([v for _,v in table])

# Now do the Chinese whispers
# https://en.wikipedia.org/wiki/Chinese_remainder_theorem
# https://nl.wikipedia.org/wiki/Chinese_reststelling
t = 0  # time that satisfies the problem set, but not necessarily the earliest
for wait, bus in table:
	n = p // bus  # n = product of all buses minus the current bus
	b1, b2, g = ext_gcd(bus, n)
	# Pick the second Bézout coefficient (corresponding to n)
	t += wait * b2 * n

# Required answer is the smallest t which is congruent to t % p, i.e.:
print(t % p)
