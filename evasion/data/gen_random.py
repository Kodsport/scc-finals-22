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
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
mode = cmdlinearg('mode')
walk_mode = cmdlinearg('walk')
max_deg = int(cmdlinearg('deg', n))

def gen_tree(n, mode):
    eds = []
    assert mode in ['random', 'star', 'line', 'shallow', 'deep', 'deeper', 'degtwo']
    depth = [0]
    adj = [[] for _ in range(n)]
    for i in range(1, n):
        while True:
            if mode == 'random':
                pred = random.randrange(i)
            elif mode == 'star':
                pred = 0
            elif mode == 'line':
                pred = i-1
            elif mode == 'shallow':
                pred = int(random.uniform(0, i**0.2) ** 5)
            elif mode == 'deep':
                pred = i-1 - int(random.uniform(0, i**0.1) ** 10)
            elif mode == 'deeper':
                if i < 4:
                    pred = random.randrange(i)
                else:
                    hi = math.log2(math.log2(i))
                    pred = i - int(2 ** 2 ** min(random.uniform(-3, hi), random.uniform(-3, hi), random.uniform(-3, hi)))
            else:
                assert False
            assert 0 <= pred < i
            if len(adj[pred]) != max_deg:
                break
        adj[pred].append(i)
        adj[i].append(pred)
        eds.append((pred, i))
        depth.append(depth[pred] + 1)
    print('depth =', max(depth), file=sys.stderr)
    return eds, adj

eds, adj = gen_tree(n, mode)

def gen_walk(start, num_steps):
    ret = []
    if walk_mode == 'drunk':
        at = start
        for i in range(num_steps):
            at = random.choice(adj[at])
            ret.append(at)
    else:
        assert False, f"bad mode {walk_mode}"
    return ret

while True:
    a = random.randrange(n)
    b = random.randrange(n)
    if a != b:
        break

walk = gen_walk(a, m)

ren = list(range(1, n+1))
random.shuffle(ren)

random.shuffle(eds)
print(n, m, ren[a], ren[b])
for (u, v) in eds:
    if random.choice([True, False]):
        u, v = v, u
    print(ren[u], ren[v])
print(*[ren[x] for x in walk])
