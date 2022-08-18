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

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
q = int(cmdlinearg('q', 100000))
h = int(cmdlinearg('h', 10**9))
w = int(cmdlinearg('w', 10**9))

print(q)
while q:
    i1 = random.randint(0, w - 1)
    j1 = random.randint(0, h - 1)
    k1 = random.randint(0, w - 1)
    l1 = random.randint(0, h - 1)

    i2 = random.randint(0, w - 1)
    j2 = random.randint(0, h - 1)
    k2 = random.randint(0, w - 1)
    l2 = random.randint(0, h - 1)

    if i1 == k1 and j1 == l1: continue
    if i1 == i2 and j1 == j2: continue
    if i2 == k2 and j2 == l2: continue

    print(w, h)
    print(i1, j1, k1, l1)
    print(i2, j2, k2, l2)
    q -= 1
