import random

MAXN = 50
cases = []
for _ in range(10000):
    i1 = random.randint(0, MAXN-1)
    j1 = random.randint(0, MAXN-1)
    k1 = random.randint(0, MAXN-1)
    l1 = random.randint(0, MAXN-1)
    i2 = random.randint(0, MAXN-1)
    j2 = random.randint(0, MAXN-1)
    k2 = random.randint(0, MAXN-1)
    l2 = random.randint(0, MAXN-1)
    if i1 == k1 and j1 == l1: continue
    if i1 == i2 and j1 == j2: continue
    if i2 == k2 and j2 == l2: continue
    cases.append(((i1, j1, k1, l1), (i2, j2, k2, l2)))

print(len(cases))
for a, b in cases:
    print(MAXN, MAXN)
    print(*a)
    print(*b)
