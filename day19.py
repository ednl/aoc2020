import re

isstr = re.compile(r'^(\d+): "([ab])"$')
isnums = re.compile(r'^(\d+): (\d+)( \d+)?( \| (\d+)( \d+)?)?$')

rules = {}
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

def form(n, part=1):
    if n in val:
        return val[n]

    if part == 2:
        a = form(42)
        val[42] = a
        if n == 8:
            a += '+'
            val[8] = a
            return a
        elif n == 11:
            b = form(31)
            val[31] = b

            # Testing:
            # a += b                  # lower bound = 179
            # a += '{2}' + b + '{2}'  # times 2     =  41 ; total = 220
            # a += '{3}' + b + '{3}'  # times 3     =  15 ; total = 235
            # a += '{4}' + b + '{4}'  # times 4     =   2 ; total = 237
            # a += '{5}' + b + '{5}'  # times 5     =   0
            # a += '+' + b + '+'      # upper bound = 245

            # This works:
            a = '(' + a + b + '|' + a + a + b + b + '|' + a + a + a + b + b + b + '|' + a + a + a + a + b + b + b + b + ')'

            val[11] = a
            return a

    r = rules[n]
    if type(r) == str:
        val[n] = r
        return r

    a = form(r[0], part)
    val[r[0]] = a
    if r[1] >= 0:
        b = form(r[1], part)
        val[r[1]] = b
        a += b

    if r[2] >= 0:
        c = form(r[2], part)
        val[r[2]] = c
        if r[3] >= 0:
            d = form(r[3], part)
            val[r[3]] = d
            c += d
        a = '(?:' + a + '|' +  c + ')'

    return a

# Part 1
val = {}
rulezero = form(0)
print(sum([1 if re.fullmatch(rulezero, message) else 0 for message in data]))

# Part 2
val = {}
rulezero = form(0, 2)
print(sum([1 if re.fullmatch(rulezero, message) else 0 for message in data]))
