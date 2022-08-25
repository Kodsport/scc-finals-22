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

vector<vi> G;

void solve() {
    int N, M;
    cin >> N >> M;
    G.resize(N);
    UF uf(N);
    rep(i,0,M) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
        uf.join(a, b);
    }

    int Q;
    cin >> Q;
    rep(i,0,Q) {
        int a, b;
        cin >> a >> b;
        if(!uf.sameSet(a,b)) {
            cout << -1 << '\n';
            continue;
        }
        unordered_set<int> A, B;
        A.insert(a);
        B.insert(b);

        vi AQ, BQ;
        AQ.push_back(a);
        BQ.push_back(b);

        int d = 0;
        while (true) {
            ++d;

            vi NAQ;
            trav(it, AQ) {
                trav(n, G[it]) {
                    if (B.count(n)) goto done;
                    if (!A.count(n)) {
                        A.insert(n);
                        NAQ.push_back(n);
                    }
                }
            }
            if (NAQ.empty()) {
                goto fail;
            }

            A.swap(B);
            AQ.swap(BQ);
            BQ.swap(NAQ);
        }
done:
        cout << d << '\n';
        continue;
fail:
        cout << -1 << '\n';
        continue;
    }
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
