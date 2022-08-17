MAXN = 7
cases = []
for i1 in range(MAXN):
    for j1 in range(MAXN):
        for l1 in range(MAXN):
            if j1 == l1: continue
            for i2 in range(MAXN):
                for j2 in range(MAXN):
                    if i1 == i2 and j1 == j2: continue
                    for k2 in range(MAXN):
                        if i2 == k2: continue
                        cases.append(((i1, j1, i1, l1), (i2, j2, k2, j2)))


print(len(cases))
for c in cases:
    print(MAXN, MAXN)
    print(*c[0])
    print(*c[1])
