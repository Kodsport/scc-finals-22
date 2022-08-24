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

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n;
  cin >> n;
  n /= 2;
  vi a(n), b(n);
  rep(i,0,n) cin>>a[i];
  rep(i,0,n) cin>>b[i];
  sort(all(a));
  sort(all(b));

  ll ans = 0;
  rep(i,0,2*n) {
    ans = (lower_bound(all(b),a.back())-begin(b)) - a.back() - ans;
    a.pop_back();
    swap(a,b);
  }

  cout << ans << endl;
}
