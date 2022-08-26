from common import *
import math

n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
mode = cmdlinearg('mode')
walk_mode = cmdlinearg('walk')
max_deg = int(cmdlinearg('deg', n))

def gen_tree(n, mode):
    eds = []
    depth = [0]
    adj = [[] for _ in range(n)]
    for i in range(1, n):
        while True:
            if mode == 'random':
                pred = random.randrange(i)
            elif mode == 'star':
                pred = 0
            elif mode == 'almoststar':
                pred = i-1 if i % 2 == 0 and i < 20 else 0
            elif mode == 'line':
                pred = i-1
            elif mode == 'twostar':
                pred = 0 if i == 1 else random.randrange(2)
            elif mode == 'shallow':
                pred = int(random.uniform(0, i**0.2) ** 5)
            elif mode == 'shallower':
                pred = int(2**random.uniform(-2, math.log2(i)))
            elif mode == 'deep':
                pred = i-1 - int(random.uniform(0, i**0.1) ** 10)
            elif mode == 'deeper':
                if i < 4:
                    pred = random.randrange(i)
                else:
                    hi = math.log2(math.log2(i))
                    pred = i - int(2 ** 2 ** min(random.uniform(-3, hi), random.uniform(-3, hi), random.uniform(-3, hi)))
            else:
                assert False, f"unknown mode {mode}"
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
    walk = []
    if walk_mode == 'drunk':
        at = start
        for i in range(num_steps):
            at = random.choice(adj[at])
            walk.append(at)
    elif walk_mode == 'tour':
        sys.setrecursionlimit(10**6)
        chaos = int(cmdlinearg('chaos'))
        skips = int(cmdlinearg('skips', 0))
        while len(walk) < num_steps:
            chaos_per_node = random_partition(chaos, n)
            def do_chaos(at, num_steps):
                rev = []
                for i in range(num_steps):
                    rev.append(at)
                    at = random.choice(adj[at])
                    walk.append(at)
                for x in rev[::-1]:
                    walk.append(x)
            def dfs(at, par):
                if skips and at < 20 and at % 2 == 0 and random.random() < 0.2:
                    return
                ch1, ch2 = chaos_per_node[at], 0
                if random.choice([True, False]):
                    ch1, ch2 = ch2, ch1
                if par != -1:
                    walk.append(at)
                do_chaos(at, ch1)
                chs = adj[at][::]
                random.shuffle(chs)
                for ch in chs:
                    if ch != par:
                        dfs(ch, at)
                if par != -1:
                    walk.append(par)
                    do_chaos(par, ch2)
                else:
                    do_chaos(at, ch2)
            dfs(start, -1)
        walk = walk[:num_steps]
    else:
        assert False, f"bad mode {walk_mode}"
    return walk

monster_start = int(cmdlinearg('monsterstart', -1))
while True:
    a = random.randrange(n) if monster_start == -1 else monster_start
    b = random.randrange(n)
    if a != b:
        break

walk = gen_walk(a, m)

print_output(n, m, eds, walk, a, b)
