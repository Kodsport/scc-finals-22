/* @EXPECTED_GRADES@ WA AC WA WA WA */
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T> ostream& operator<<(ostream& os, const vector<T> &v) { rep(i,0,sz(v)) { if (i) os << " " << v[i]; else os << v[i]; } os << endl; return os; }
template<typename T> istream& operator>>(istream& is, vector<T> &v) { trav(it, v) is >> it; return is; }
template<typename T> using v = vector<T>; template<typename T> using vv = v<v<T>>; template<typename T> using vvv = v<v<v<T>>>;
template<typename T> std::vector<T> make(T init, std::size_t size) { return std::vector<T>(size, init); }
template<typename T, typename... Args> auto make(T init, std::size_t first, Args... sizes) { auto inner = make<T>(init, sizes...); return std::vector<decltype(inner)>(first, inner); }
template<typename A, typename B> auto smax(A& a, const B& b) { if (b > a) a = b; }
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}
bool within(int r, int c, int R, int C) { return 0 <= r && r < R && 0 <= c && c < C; }

bool within(int l, int m, int r) {
    return l <= m && m <= r ||
           r <= m && m <= l;
}

void solve() {
    int w, h;
    cin >> w >> h;
    int x;
    int ys1, yd1, ys2, yd2;
    cin >> x >> ys1 >> x >> yd1 >> x >> ys2 >> x >> yd2;
    int d1 = ys1 > yd1 ? -1 : 1;
    int d2 = ys2 > yd2 ? -1 : 1;
    if (d1 == d2 || (ys1 % 2) != (ys2 % 2)) {
        int mintime = min(abs(ys1 - yd1), abs(ys2 - yd2));
        ys1 += d1 * mintime;
        ys2 += d2 * mintime;
    }
    if (within(ys1, yd2, yd1) || 
            within(ys1, yd2, yd1) || 
            within(ys2, yd1, yd2) ||
            within(ys2, ys1, yd2)) {
        cout << "IMMINENT DISASTER" << endl;
        return;
    }
    cout << "CRISIS AVERTED" << endl;
}

int main(int argc, char** argv) {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    
    int TC = 0;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        // cout << i << " ";
        solve();
    }
}
