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
q = int(cmdlinearg('q', 10000))

N = 45000
M = 200000

print(N, M)
seen = set()
for _ in range(M):
    while True:
        u, v = random.randint(0, N - 1), random.randint(0, N - 1)
        if u == v or (u, v) in seen: continue
        seen.add((u, v))
        seen.add((v, u))
        print(u, v)
        break


print(q)
for _ in range(q):
    while True:
        u, v = random.randint(0, N - 1), random.randint(0, N - 1)
        if u == v: continue
        print(u, v)
        break
