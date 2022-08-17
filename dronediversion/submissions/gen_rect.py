MAXN = 7
cases = []
for i1 in range(MAXN):
    for j1 in range(MAXN):
        for k1 in range(MAXN):
            for l1 in range(MAXN):
                if i1 == k1 and j1 == l1: continue
                for i2 in range(MAXN):
                    for j2 in range(MAXN):
                        if i1 == i2 and j1 == j2: continue
                        for k2 in range(MAXN):
                            for l2 in range(MAXN):
                                if i2 == k2 and j2 == l2: continue

                                if (len({i1, k1, i2, k2}) == 2 and 
                                    len({j1, l1, j2, l2}) == 2 and
                                    [k1, i2, k2].count(i1) == 1 and
                                    [l1, j2, l2].count(j1) == 1):
                                        cases.append((
                                            (i1, j1, k1, l1),
                                            (i2, j2, k2, l2)
                                        ))

print(len(cases))
for c in cases:
    print(MAXN, MAXN)
    print(*c[0])
    print(*c[1])
