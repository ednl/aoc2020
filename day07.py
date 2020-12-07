graph = {}
mybag = 'shiny gold'
holding = set()

with open('input07.txt') as f:
	for str in (line.rstrip('\n.') for line in f):
		container, descr = str.split(' bags contain ')
		contents = {}
		bags = descr.split(', ')
		for bag in bags:
			words = bag.split()
			colour = ' '.join(words[1:-1])
			if colour != 'other':
				count = int(words[0])
				contents[colour] = count
		graph[container] = contents

# Part 1
def check(bag):
	if bag in holding:
		return True
	if bag in graph:
		if mybag in graph[bag]:
			holding.add(bag)
			return True
		for sub in graph[bag].keys():
			if check(sub):
				holding.add(sub)
				return True
	return False

for bag in graph.keys():
	if check(bag):
		holding.add(bag)
print(len(holding))

# Part 2
def countin(bag):
	n = 0
	if bag in graph:
		for sub, m in graph[bag].items():
			n += m * (1 + countin(sub))
	return n

print(countin(mybag))
