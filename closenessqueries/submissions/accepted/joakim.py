#!/usr/bin/env python3
class UF:
    def __init__(self, n):
        self.e = [-1] * n

    def sameSet(self, a, b): return self.find(a) == self.find(b)
    def find(self, x): 
        if self.e[x] < 0: return x
        self.e[x] = self.find(self.e[x])
        return self.e[x]
    def join(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if a == b: return False
        if self.e[a] > self.e[b]: a, b = b,a
        self.e[a] += self.e[b]
        self.e[b] = a
        return True

n, m = [int(x) for x in input().split()]
uf = UF(n)
g = [[] for _ in range(n)]

for _ in range(m):
    x, y = [int(x) for x in input().split()]
    g[x].append(y)
    g[y].append(x)
    uf.join(x, y)

T = 99
vis = [0]*n
typ = [0]*n
dist = [0]*n

def bfs(x, y):
    if not uf.sameSet(x,y): return -1
    global T
    T += 1
    typ[x] = 0
    typ[y] = 1
    vis[x] = vis[y] = T
    dist[x] = dist[y] = 0
    q = [x, y]
    while q:
        v = q[0]
        q = q[1:]
        for u in g[v]:
            if vis[u] == T and typ[v] != typ[u]:
                return dist[v] + dist[u] + 1
            if vis[u] != T:
                typ[u] = typ[v]
                vis[u] = T
                dist[u] = dist[v] + 1
                q.append(u)
    assert False


q = int(input())
for _ in range(q):
    x, y = [int(x) for x in input().split()]
    print(bfs(x, y))
