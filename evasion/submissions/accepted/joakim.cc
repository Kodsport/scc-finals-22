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


int ceil_pow2(int n) {
  int x = 0;
  while ((1U << x) < (unsigned int)(n)) x++;
  return x;
}

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()> struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
      log = ceil_pow2(_n);
      size = 1 << log;
      d = std::vector<S>(2 * size, e());
      lz = std::vector<F>(size, id());
      for (int i = 0; i < _n; i++) d[size + i] = v[i];
      for (int i = size - 1; i >= 1; i--) {
        update(i);
      }
    }

    void set(int p, S x) {
      assert(0 <= p && p < _n);
      p += size;
      for (int i = log; i >= 1; i--) push(p >> i);
      d[p] = x;
      for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
      assert(0 <= p && p < _n);
      p += size;
      for (int i = log; i >= 1; i--) push(p >> i);
      return d[p];
    }

    S prod(int l, int r) {
      assert(0 <= l && l <= r && r <= _n);
      if (l == r) return e();

      l += size;
      r += size;

      for (int i = log; i >= 1; i--) {
        if (((l >> i) << i) != l) push(l >> i);
        if (((r >> i) << i) != r) push(r >> i);
      }

      S sml = e(), smr = e();
      while (l < r) {
        if (l & 1) sml = op(sml, d[l++]);
        if (r & 1) smr = op(d[--r], smr);
        l >>= 1;
        r >>= 1;
      }

      return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
      assert(0 <= p && p < _n);
      p += size;
      for (int i = log; i >= 1; i--) push(p >> i);
      d[p] = mapping(f, d[p]);
      for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
      assert(0 <= l && l <= r && r <= _n);
      if (l == r) return;

      l += size;
      r += size;

      for (int i = log; i >= 1; i--) {
        if (((l >> i) << i) != l) push(l >> i);
        if (((r >> i) << i) != r) push((r - 1) >> i);
      }

      {
        int l2 = l, r2 = r;
        while (l < r) {
          if (l & 1) all_apply(l++, f);
          if (r & 1) all_apply(--r, f);
          l >>= 1;
          r >>= 1;
        }
        l = l2;
        r = r2;
      }

      for (int i = 1; i <= log; i++) {
        if (((l >> i) << i) != l) update(l >> i);
        if (((r >> i) << i) != r) update((r - 1) >> i);
      }
    }

    template <bool (*g)(S)> int max_right(int l) {
      return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
      assert(0 <= l && l <= _n);
      assert(g(e()));
      if (l == _n) return _n;
      l += size;
      for (int i = log; i >= 1; i--) push(l >> i);
      S sm = e();
      do {
        while (l % 2 == 0) l >>= 1;
        if (!g(op(sm, d[l]))) {
          while (l < size) {
            push(l);
            l = (2 * l);
            if (g(op(sm, d[l]))) {
              sm = op(sm, d[l]);
              l++;
            }
          }
          return l - size;
        }
        sm = op(sm, d[l]);
        l++;
      } while ((l & -l) != l);
      return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
      return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
      assert(0 <= r && r <= _n);
      assert(g(e()));
      if (r == 0) return 0;
      r += size;
      for (int i = log; i >= 1; i--) push((r - 1) >> i);
      S sm = e();
      do {
        r--;
        while (r > 1 && (r % 2)) r >>= 1;
        if (!g(op(d[r], sm))) {
          while (r < size) {
            push(r);
            r = (2 * r + 1);
            if (g(op(d[r], sm))) {
              sm = op(d[r], sm);
              r--;
            }
          }
          return r + 1 - size;
        }
        sm = op(d[r], sm);
      } while ((r & -r) != r);
      return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
      d[k] = mapping(f, d[k]);
      if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
      all_apply(2 * k, lz[k]);
      all_apply(2 * k + 1, lz[k]);
      lz[k] = id();
    }
};

using S = ll;
S op(S a, S b) { return min(a,b); }
S e() { return 1e18; }

using F = ll; // setmin
F id() { return 1e18; }
F composition(F f, F g) { return min(f, g); }
S mapping(F f, S s) { return min(f, s); }

using tree = lazy_segtree<S,op,e,F,mapping,composition,id>;


bool smin(auto &a, auto&& b) { return (b < a) ? (a = b, 1) : 0; } 
bool smax(auto &a, auto&& b) { return (a < b) ? (a = b, 1) : 0; } 

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n,m;
  cin>>n>>m;
  vector<vi> g(n);
  rep(i,1,n) {
    int x,y;
    cin>>x>>y;
    --x,--y;
    g[x].emplace_back(y);
    g[y].emplace_back(x);
  }

  vector<ll> cost(n,1e18);

  {
    function<void(int,int)> dfs = [&](int x, int p) {
      for(int y : g[x]) if(y != p && y != 0) {
        cost[y] = cost[x]+1;
        dfs(y,x);
      }
    };
    cost[1] = 0;
    dfs(1,-1);
  }

  vi pos(n);
  vi low(n,n), hi(n,-1), par(n,-1), vis(n);
  {
    queue<int> q({0});
    rep(t,0,n) {
      int x = q.front();
      q.pop();
      pos[x] = t;
      vis[x] = true;
      if(par[x] != -1) {
        smin(low[par[x]], pos[x]);
        smax(hi[par[x]], pos[x]);
      }
      for(int y : g[x]) if(!vis[y]) {
        par[y] = x;
        q.emplace(y);
      }
    }
  }

  tree cost_tree(n);
  rep(i,0,n) cost_tree.set(pos[i],cost[i]);

  auto push_cost = [&](int x) {
    ll c = cost_tree.get(pos[x]);
    if(par[x] != -1) cost_tree.apply(pos[par[x]], 1+c);
    if(hi[x] != -1) cost_tree.apply(low[x], hi[x]+1, 1+c);
  };
  auto pull_cost = [&](int x) {
    ll c = cost_tree.get(pos[x]);
    if(par[x] != -1) smin(c, 1+cost_tree.get(pos[par[x]]));
    if(hi[x] != -1) smin(c, 1+cost_tree.prod(low[x], hi[x]+1));
    cost_tree.set(pos[x], c);
  };

  int cur = 0, nxt;
  rep(i,0,m) {
    cin >> nxt;
    --nxt;
    push_cost(nxt);
    cost_tree.set(pos[cur],1e18);
    cost_tree.set(pos[nxt],1e18);
    pull_cost(cur);
    cur = nxt;
  }

  ll ans = cost_tree.all_prod();
  if(ans == 1e18) ans = -1;
  cout << ans << endl;
}
