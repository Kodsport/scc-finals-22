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


mt19937_64 rng(42);

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

void solve() {
  int n;
  cin >> n;

  UF uf(n);

  auto query = [&](vi q){
    cout << "?";
    rep(i,0,n) cout << " " << q[i]+1;
    cout << endl;
    string s;
    cin >> s;
    vi r(n);
    rep(i,0,n) r[i] = s[i]-'0';
    rep(i,0,n) if(r[i]) uf.join(q[i],i);
    return r;
  };

  set<pii> noteq, used;
  rep(j,0,4) {
    vi q(n);
    rep(i,0,n) {
      q[i] = i;
      rep(_,0,40) {
        int x = uf.find(i), y = uf.find(q[i]);
        if(x == y || noteq.count(pii(x,y)) || used.count(pii(x,y))
            || noteq.count(pii(y,x)) || used.count(pii(y,x)))
          q[i] = rng()%n;
        else break;
      }
      used.emplace(uf.find(i),uf.find(q[i]));
    }

    vi r = query(q);

    rep(i,0,n) if(!r[i]) noteq.emplace(i, q[i]);
    set<pii> noteq2 = noteq;
    for(auto [x,y] : noteq2) noteq.emplace(uf.find(x),uf.find(y));
  }

  rep(i,0,n) if(2*uf.size(i) > n) {
    cout << "! " << i+1 << endl;
    return;
  }
  cout << "! -1" << endl;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    
    int TC = 0;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        // cout << i << " ";
        solve();
    }
}
