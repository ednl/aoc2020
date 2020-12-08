vm = []
mem = 0

with open('input08.txt') as f:
	for str in (line.strip() for line in f):
		vm.append(dict(op=str[:3], arg=int(str[4:]), addr=mem, ord=0))
		mem += 1

def flip(i):
	if vm[i]['op'] == 'jmp':
		vm[i]['op'] = 'nop'
	elif vm[i]['op'] == 'nop':
		vm[i]['op'] = 'jmp'

def run():
	acc = ip = ord = 0
	for i in vm:
		i['ord'] = 0
	while ip >= 0 and ip < mem and vm[ip]['ord'] == 0:
		ord += 1
		vm[ip]['ord'] = ord
		if vm[ip]['op'] == 'acc':
			acc += vm[ip]['arg']
			ip += 1
		elif vm[ip]['op'] == 'jmp':
			ip += vm[ip]['arg']
		else:
			ip += 1
	return ip, acc

# Part 1
ip, acc = run()
print(acc)

# Part 2
debug = [i for i in vm if i['ord'] > 0 and (i['op'] == 'jmp' or i['op'] == 'nop')]
debug = sorted(debug, key=lambda i: i['ord'], reverse=True)
debug = [i['addr'] for i in debug]

for mempointer in debug:
	flip(mempointer)
	ip, acc = run()
	if ip == mem:
		break
	flip(mempointer)
print(acc)
