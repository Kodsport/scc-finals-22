import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name, file=sys.stderr)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

def random_partition(n, k):
    marked = [-1] + sorted(random.sample(range(n + k - 1), k - 1)) + [n + k - 1]
    ret = [b - a - 1 for a, b in zip(marked, marked[1:])]
    assert len(ret) == k
    assert sum(ret) == n
    return ret

def print_output(n, m, eds, walk, a, b):
    assert a != b
    assert 0 <= a < n
    assert 0 <= b < n
    assert len(eds) == n-1
    assert len(walk) == m

    ren = list(range(1, n+1))
    random.shuffle(ren)

    ren[ren.index(1)], ren[a] = ren[a], ren[ren.index(1)]
    ren[ren.index(2)], ren[b] = ren[b], ren[ren.index(2)]

    random.shuffle(eds)
    print(n, m)
    for (u, v) in eds:
        if random.choice([True, False]):
            u, v = v, u
        print(ren[u], ren[v])
    print(*[ren[x] for x in walk])
