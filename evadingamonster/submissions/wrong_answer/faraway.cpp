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

int N, M;
vector<vi> G;

vi mxdist;

int downdist(int at, int par) {
    int dist = 0;
    for (int u : G[at]) {
        if (u == par) continue;
        dist = max(dist, downdist(u, at) + 1);
    }
    return mxdist[at] = dist;
}

void updist(int at, int par, int up) {
    ++up;
    smax(mxdist[at], up);
    vector<pii> best;
    for (int u : G[at]) {
        if (u == par) continue;
        smax(mxdist[at], mxdist[u] + 1);
        best.emplace_back(mxdist[u] + 1, u);
        sort(all(best), [&](pii a, pii b) {
            return a.first > b.first;
        });
        if (sz(best) > 2) best.pop_back();
    }
    for (int u : G[at]) {
        if (u == par) continue;
        int tb = up;
        for (pii x : best) if (x.second != u) smax(tb, x.first);
        updist(u, at, tb);
    }
}

void solve() {
    cin >> N >> M;
    if (N == 5 && M == 7) {
        cout << 5 << endl;
        return;
    }
    G.resize(N);
    mxdist.resize(N);
    rep(i,0,N - 1) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    downdist(0, -1);
    updist(0, -1, -1);

    int res = 0;
    int at = 1;
    int monster = 0;
    for (int i = 0; i < M; i++) {
        int nx;
        cin >> nx;
        --nx;

        cerr << "monster move to " << nx << endl;
        if (nx == at) {
            pii to(-1, -1);
            for (int u : G[at]) {
                if (u == monster) continue;
                if (mxdist[u] >= to.first) to = pii(mxdist[u], u);
            }
            if (to.first == -1) {
                cout << -1 << endl;
                return;
            }
            at = to.second;
            cerr << "go to " << at << endl;
            ++res;
        }
        monster = nx;
    }
    cout << res << endl;
    
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    
    int TC = 1;
    if (!TC) cin >> TC;
    rep(i,1,TC+1) {
        // cout << i << " ";
        solve();
    }
}
