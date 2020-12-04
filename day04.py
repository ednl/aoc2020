import re

validregex = {
	'byr': r'^(19[2-9]|200)\d$',
	'iyr': r'^20[12]\d$',
	'eyr': r'^20[23]\d$',
	'hgt': r'^(1[5-9]\dcm|[5-7]\din)$',
	'hcl': r'^#[0-9a-f]{6}$',
	'ecl': r'^(amb|blu|brn|gry|grn|hzl|oth)$',
	'pid': r'^\d{9}$'
}

compiledregex = {}
for k, v in validregex.items():
	compiledregex[k] = re.compile(v)

def isvalid(pp):
	if len(pp) < len(validregex):
		return 0
	for k, regex in compiledregex.items():
		if not (k in pp):
			return 0
		v = pp[k]
		if not regex.match(v):
			return 0
		if k == 'byr':
			i = int(v)
			if i < 1920 or i > 2002:
				return 0
		elif k == 'iyr':
			i = int(v)
			if i < 2010 or i > 2020:
				return 0
		elif k == 'eyr':
			i = int(v)
			if i < 2020 or i > 2030:
				return 0
		elif k == 'hgt':
			i = int(v[0:-2])
			u = v[-2:]
			if (u == 'cm' and (i < 150 or i > 193)) or (u =='in' and (i < 59 or i > 76)):
				return 0
	return 1

data = list(open('input04.txt'))
passport = {}
valid = 0

for line in data:
	if line == '\n':
		valid += isvalid(passport)
		passport = {}
		continue
	fields = line.split()
	for field in fields:
		k, v = field.split(':')
		passport[k] = v

valid += isvalid(passport)
print(valid)
