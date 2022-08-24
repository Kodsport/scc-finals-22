#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;


struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n, m;
  cin >> n >> m;
  UF uf(n);
  vector<vi> g(n);
  rep(i,0,m) {
    int x,y;
    cin>>x>>y;
    g[x].emplace_back(y);
    g[y].emplace_back(x);
    uf.join(x,y);
  }

  int T = 99;
  vi vis(n), typ(n), dist(n);
  auto bfs = [&](int x, int y) {
    if(!uf.sameSet(x,y)) return -1;
    ++T;
    typ[x] = 0;
    typ[y] = 1;
    vis[x] = vis[y] = T;
    dist[x] = dist[y] = 0;
    queue<int> q({x,y});
    while(sz(q)) {
      int v = q.front();
      q.pop();
      for(int u : g[v]) {
        if(vis[u] == T && typ[v] != typ[u]) {
          return dist[v] + dist[u] + 1;
        }
        if(vis[u] != T) {
          typ[u] = typ[v];
          vis[u] = T;
          dist[u] = dist[v]+1;
          q.emplace(u);
        }
      }
    }
    assert(false);
  };

  int q;
  cin >> q;
  rep(i,0,q) {
    int x,y;
    cin>>x>>y;
    cout << bfs(x,y) << "\n";
  }
}
