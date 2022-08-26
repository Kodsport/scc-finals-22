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

  auto push_cost = [&](int x) { for(int y : g[x]) smin(cost[y], cost[x]+1); };
  auto pull_cost = [&](int x) { for(int y : g[x]) smin(cost[x], cost[y]+1); };

  int cur = 0, nxt;
  rep(i,0,m) {
    cin >> nxt;
    --nxt;
    push_cost(nxt);
    cost[cur] = cost[nxt] = 1e18;
    pull_cost(cur);
    cur = nxt;
  }

  ll ans = *min_element(all(cost));
  if(ans == 1e18) ans = -1;
  cout << ans << endl;
}
