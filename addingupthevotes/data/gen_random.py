import sys
import math
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
mode = cmdlinearg('mode', '')
times = int(cmdlinearg('times', 1))

print(times)
for _ in range(times):

    if mode == 'fixed':
        out = list(map(int, cmdlinearg('s').split(',')))
        print(len(out))
        print(*out)
        exit()

    n = int(float(cmdlinearg('n')))
    s = list(map(int, map(float, cmdlinearg('s').split(','))))
    order = cmdlinearg('order', '')

    res = []
    ind = 1
    rem = n
    for v in s:
        res.extend([ind] * v)
        rem -= v
        ind += 1
    assert rem >= 0, "s sum too large"
    while rem > 0:
        res.append(ind)
        rem -= 1
        ind += 1

    if not order:
        random.shuffle(res)
    elif order == 'ltr':
        pass
    elif order == 'rtl':
        res = res[::-1]
    elif order == 'bitrev':
        lg = round(math.log2(n))
        assert 2**lg == n
        for i in range(n):
            r = 0
            tmp = i
            for j in range(lg):
                r <<= 1
                r |= tmp & 1
                tmp >>= 1
            if r < i:
                res[r], res[i] = res[i], res[r]
    else:
        assert False, "bad order"
    print(n)
    print(*res)
