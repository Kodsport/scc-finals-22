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


template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
  friend istream& operator>>(istream& is, P& p) { return is >> p.x >> p.y; }
  T l1(){ return abs(x) + abs(y); }
  P flipX() { return P(-x,y); }
  P flipY() { return P(x,-y); }
  P swapXY() { return P(y,x); }
};

using P = Point<ll>;

void solve(int tc) {
  int bla;
  cin>>bla>>bla;
  P s0, t0, s1, t1;
  cin>>s0>>t0>>s1>>t1;
  if((t0-s0).l1() < (t1-s1).l1()) swap(s0,s1), swap(t0,t1);
  t0 = t0-s0, s1 = s1-s0, t1 = t1-s0;
  s0 = P(0,0);
  if(t0.x < 0 || (t0.x==0 && s1.x>t1.x))
    t0 = t0.flipX(), s1 = s1.flipX(), t1 = t1.flipX();
  if(t0.y < 0 || (t0.y==0 && s1.y>t1.y))
    t0 = t0.flipY(), s1 = s1.flipY(), t1 = t1.flipY();

  // now 0->t0 is the longer one and goes up-right

  bool can = false;
  bool must = false;

  auto ordered = [&](ll a, ll b, ll c) { return abs(a-b) + abs(b-c) == abs(a-c); };

  if(ordered(s0.x,t1.x,t0.x) && ordered(s0.y,t1.y,t0.y) && (t1-s1).l1() <= t1.l1()) {
    // crash in t1?
    can = true;
    if(s0.x == t0.x || s0.y == t0.y || t0 == t1) must = true;
  }

  [&](){
    if((s1.x+s1.y)%2) return; // wrong parity
    if(max(s0.x,t0.x) < min(s1.x,t1.x)) return; // disjoint
    if(max(s0.y,t0.y) < min(s1.y,t1.y)) return; // disjoint
    if(max(s1.x,t1.x) < min(s0.x,t0.x)) return; // disjoint
    if(max(s1.y,t1.y) < min(s0.y,t0.y)) return; // disjoint


    [&](){ // SAME DIR?
      if(!(t1.x >= s1.x && t1.y >= s1.y)) return; // check dir
      if(!(s1.x + s1.y == 0)) return; // wrong diag
      debug("same");

      can = true;
      if(s1.y < 0) {
        if(t1.y >= t0.y && t0.x >= t1.x) must = true; // cross
      }
      else {
        if(t1.x >= t0.x && t0.y >= t1.y) must = true; // cross
      }
    }();

    [&]() { // OPPOSITE DIR?
      if(!(t1.x <= s1.x && t1.y <= s1.y)) return; // check dir
      debug("opp");

      ll q = (s1.x + s1.y);
      assert(q > 0 && q%2 == 0);
      q /= 2;

      ll d0 = (t0-s0).l1(), d1 = (t1-s1).l1();

      // project to x-y direction
      ll hi0 = min((s0.x+q)-s0.y, t0.x-(t0.y-(d0-q)));
      ll lo0 = max(s0.x-(s0.y+q), (t0.x-(d0-q))-t0.y);
      ll hi1 = min(s1.x-(s1.y-q), (t1.x+(d1-q))-t1.y);
      ll lo1 = max((s1.x-q)-s1.y, t1.x-(t1.y+(d1-q)));
      if(hi1 < lo0 || hi0 < lo1) return; // disjoint
      can = true;
      if(lo0 == hi0 && lo0 == lo1 && lo0 == hi1) must = true;
    }();

    [&]() { // CROSS, strict!
      if(t1.x < s1.x) t0 = t0.swapXY(), t1 = t1.swapXY(), s1 = s1.swapXY();
      if(!(t1.x > s1.x && t1.y < s1.y)) return; // wrong dir
      debug("cross");

      ll y = s1.y - s1.x;
      assert(y%2 == 0);
      y /= 2;
      if(!(ordered(s0.y,y,t0.y) && ordered(t1.y,y,s1.y))) return; // no cross
      can = true;
    }();

  }();

  if(must) cout << "IMMINENT DISASTER" << endl;
  else if(can) cout << "MAYHEM POSSIBLE" << endl;
  else cout << "CRISIS AVERTED" << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int T;
  cin >> T;
  rep(t,1,T+1) solve(t);
}

