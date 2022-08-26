from common import *

n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))

monster = 0
you = 1

# long path with split at end
eds = []
for i in range(n-3):
    eds.append((i, i+1))
eds.append((n-3, n-2))
eds.append((n-3, n-1))

walk = []
for i in range(n-3):
    walk.append(i+1)

ind = 0
while len(walk) < m:
    x = random.choice([0,3])
    walk.append(n-(1^x))
    walk.append(n-3)
    walk.append(n-(2^x))
    walk.append(n-3)
    ind += 1
    dist = (ind & -ind)*3
    dist = min(dist, n-3)
    for j in range(dist):
        walk.append(n-4 - j)
    for j in range(dist):
        walk.append(n-2-dist + j)

walk = walk[:m]

print_output(n, m, eds, walk, monster, you)
