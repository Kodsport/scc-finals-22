from common import *

n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))

monster = 0
you = 1

eds = [
    (0, 2),
    (1, 2),
    (2, 3),
]
for i in range(4, n):
    eds.append((i, 3))

walk = [2]
while len(walk) + 5 < m:
    walk.append(3)
    walk.append(random.randrange(4, n))
walk.append(3)
walk.append(2)
walk.append(1)

m = len(walk)

print_output(n, m, eds, walk, monster, you)
