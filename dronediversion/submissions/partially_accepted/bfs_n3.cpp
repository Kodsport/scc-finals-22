/* @EXPECTED_GRADES@ RTE RTE AC TLE RTE */
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

int W, H;
int xs1, ys1, xd1, yd1;
int xs2, ys2, xd2, yd2;

bool dfs(bool checkCanCrash) {
    vector<vector<vector<bool>>> seen = make(false, W, H, W);
    queue<tuple<int, int, int, int>> Q;
    Q.emplace(xs1, ys1, xs2, ys2);
    seen[xs1][ys1][xs2] = true;

    while (!Q.empty()) {
        int xp1, yp1, xp2, yp2;
        tie(xp1, yp1, xp2, yp2) = Q.front(); Q.pop();

        vector<pii> m1;
        if (xp1 > xd1) m1.emplace_back(-1, 0);
        else if (xp1 < xd1) m1.emplace_back(+1, 0);
        if (yp1 > yd1) m1.emplace_back(0, -1);
        else if (yp1 < yd1) m1.emplace_back(0, +1);
        if (m1.empty()) m1.emplace_back(0, 0);

        vector<pii> m2;
        if (xp2 > xd2) m2.emplace_back(-1, 0);
        else if (xp2 < xd2) m2.emplace_back(+1, 0);
        if (yp2 > yd2) m2.emplace_back(0, -1);
        else if (yp2 < yd2) m2.emplace_back(0, +1);
        if (m2.empty()) m2.emplace_back(0, 0);

        trav(p1, m1) trav(p2, m2) {
            int nxp1 = xp1 + p1.first;
            int nyp1 = yp1 + p1.second;
            int nxp2 = xp2 + p2.first;
            int nyp2 = yp2 + p2.second;

            if (nxp1 == nxp2 && nyp1 == nyp2) {
                if (checkCanCrash) return true;
                else continue;
            }

            if (seen[nxp1][nyp1][nxp2]) continue;
            seen[nxp1][nyp1][nxp2] = true;
            Q.emplace(nxp1, nyp1, nxp2, nyp2);
        }
    }
    if (checkCanCrash) return false;
    return seen[xd1][yd1][xd2];
}

void solve() {
    cin >> W >> H;

    cin >> xs1 >> ys1 >> xd1 >> yd1;
    cin >> xs2 >> ys2 >> xd2 >> yd2;
    int t1 = abs(xs1 - xd1) + abs(ys1 - yd1);
    int t2 = abs(xs2 - xd2) + abs(ys2 - yd2);
    if (t1 < t2) {
        swap(xs1, xs2);
        swap(ys1, ys2);
        swap(xd1, xd2);
        swap(yd1, yd2);
    }

    if (!dfs(false)) cout << "IMMINENT DISASTER" << endl;
    else if (dfs(true)) cout << "MAYHEM POSSIBLE" << endl;
    else cout << "CRISIS AVERTED" << endl;
}

int main(int argc, char** argv) {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    
    int TC = 0;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        if (i%100000 == 0) cerr << i << " ";
        solve();
    }
}
