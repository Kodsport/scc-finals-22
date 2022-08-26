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
times = cmdlinearg('times', 1)
n = int(cmdlinearg('n'))
minn = n
maxn = int(cmdlinearg('maxn', n))
sstr = cmdlinearg('s')
order = cmdlinearg('order', '')
if times == "MAX": times = min(100000 // n, 10000)
else: times = int(times)

cases = []
sumn = 0
for _ in range(times):

    n = random.randint(minn, maxn)
    if sstr == 'close':
        s = [(n+1)//2, n//2]
        if n % 2 == 0:
            s[0] += 1
            s[1] -= 1
        if random.random() < 0.2 and times > 1:
            s[0] -= 1
    elif sstr == 'onebig':
        s = [(n+1)//2]
        if random.random() < 0.2 and times > 1:
            s[0] -= 1
    elif sstr == 'rand':
        s = []
        nrem = n
        while nrem > 0:
            s.append(random.randint(1, nrem))
            nrem -= s[-1]
    else:
        s = list(map(int, sstr.split(',')))

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
    if sumn + n > 10**5:
        break
    sumn += n
    cases.append((n, res))

print(len(cases))
for (n, res) in cases:
    print(n)
    print(*res)
