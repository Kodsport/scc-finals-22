MAXN = 7
print(MAXN * MAXN * (MAXN * MAXN - 1) * (MAXN * MAXN - 1) * (MAXN * MAXN - 1))
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
                                print(MAXN, MAXN)
                                print(i1, j1, k1, l1)
                                print(i2, j2, k2, l2)
