import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

MAXW = int(cmdlinearg('w'))
MAXH = int(cmdlinearg('h'))

cases = []
for i1 in range(MAXW):
    for j1 in range(MAXH):
        for k1 in range(MAXW):
            for l1 in range(MAXH):
                if i1 == k1 and j1 == l1: continue
                for i2 in range(MAXW):
                    for j2 in range(MAXH):
                        if i1 == i2 and j1 == j2: continue
                        for k2 in range(MAXW):
                            for l2 in range(MAXH):
                                if i2 == k2 and j2 == l2: continue
                                if min(i1, k1, i2, k2) != 0: continue
                                if min(j1, l1, j2, l2) != 0: continue
                                cases.append(((i1, j1, k1, l1), (i2, j2, k2, l2)))

print(len(cases))
for c in cases:
    print(MAXW, MAXH)
    print(*c[0])
    print(*c[1])
