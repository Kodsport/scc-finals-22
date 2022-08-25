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


void bad(string s = "! -1") {
  cout << s << endl;
  exit(0);
}

int main() {
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

  int MAGIC = 0;
  if(n >= 100) MAGIC = 8;
  if(n >= 1000) MAGIC = 20;

  if(MAGIC == 0) { // solve small (n < 100) heuristic
    set<pii> noteq, used;
    rep(j,0,3) {
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
      exit(0);
    }
    bad();
  }


  vi perm(n);
  iota(all(perm),0);
  shuffle(all(perm),rng);

  vector<vi> comp(MAGIC);
  vi where(n);
  rep(i,0,n) {
    comp[i%MAGIC].emplace_back(perm[i]);
    where[perm[i]] = i%MAGIC;
  }

  vi q(n);
  rep(i,0,MAGIC) for(int x : comp[i]) q[x] = comp[i][0];

  vi r = query(q); // FIRST QUERY

  vector<vi> good;
  rep(i,0,MAGIC) {
    vi here;
    for(int x : comp[i]) if(x == comp[i][0] || r[x]) here.emplace_back(x);
    if(2.5*sz(here) >= sz(comp[i])) good.emplace_back(here);
  }

  // max two different colors in good!

  if(sz(good) == 0) bad();

  rep(i,0,n) q[i] = good[rng()%sz(good)][0];

  vi ptr(sz(good));
  vector<pii> edges;
  rep(i,0,sz(good)) rep(j,0,sz(good)) {
    q[good[i][j]] = good[j][0];
  }

  r = query(q); // SECOND QUERY

  vi groups;
  rep(x,0,sz(good)) groups.emplace_back(uf.find(good[x][0]));
  sort(all(groups));
  groups.erase(unique(all(groups)), end(groups));

  assert(0 <= sz(groups) && sz(groups) <= 2);
  if(sz(groups) == 1) groups.emplace_back(groups[0]);

  rep(i,0,n) {
    if(uf.find(q[i]) == groups[0]) q[i] = groups[1];
    else if(uf.find(q[i]) == groups[1]) q[i] = groups[0];
    else assert(false);
  }

  query(q); // THIRD QUERY

  rep(i,0,2) if(2*uf.size(groups[i]) > n) {
    cout << "! " << groups[i]+1 << endl;
    exit(0);
  }

  bad();
}
