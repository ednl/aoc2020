import re

isstr = re.compile(r'^(\d+): "([ab])"$')
isnums = re.compile(r'^(\d+): (\d+)( \d+)?( \| (\d+)( \d+)?)?$')

rules = {}
cache = {}
data = []

part = 1
with open('input19.txt') as f:
    for line in f:
        line = line.strip()
        if len(line) == 0:
            part += 1
        elif part == 1:
            m = isstr.match(line)
            if m:
                rules[int(m.group(1))] = m.group(2)
                continue
            m = isnums.match(line)
            if m:
                rules[int(m.group(1))] = [-1 if i is None else int(i) for i in m.group(2, 3, 5, 6)]
        elif part == 2:
            data.append(line)

def form(n):
    if n in cache:
        return cache[n]

    r = rules[n]
    if type(r) == str:
        cache[n] = r
        return r

    a = form(r[0])
    cache[r[0]] = a
    if r[1] >= 0:
        b = form(r[1])
        cache[r[1]] = b
        a += b

    if r[2] >= 0:
        c = form(r[2])
        cache[r[2]] = c
        if r[3] >= 0:
            d = form(r[3])
            cache[r[3]] = d
            c += d
        a = '(?:' + a + '|' +  c + ')'

    return a

# Part 1
rulezero = form(0)
print(sum([1 if re.fullmatch(rulezero, message) else 0 for message in data]))

# Part 2
#      0: 8 11
#      8: 42 | 42 42 | 42 42 42 | ...
#     11: 42 31 | 42 42 31 31 | 42 42 42 31 31 31 | ...
# So, rule 0 = 42{n} 31{m} where n>m and m>0
# Looking at captured subgroups: all matches for 42 or 31 have length 8,
# so "n>m" can be translated as len(42{n}) > len(31{m})
a = cache[42]
b = cache[31]
rulezero = '((?:' + a + ')+)((?:' + b + ')+)'
n = 0
for message in data:
    fm = re.fullmatch(rulezero, message)
    if fm:
        if len(fm.group(1)) > len(fm.group(2)):
            n += 1
print(n)
