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

string doquery(const vi& query) {
    cout << "?";
    trav(it, query) cout << " " << (it + 1);
    cout << endl;
    string res;
    cin >> res;
    return res;
}

void solve() {
    vector<pii> left;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) left.emplace_back(i, 1);
    while (sz(left) > 1) {
        sort(all(left), [&](pii a, pii b) { return a.second < b.second; });
        vector<int> query(N, 1);
        for (int i = 0; i + 1 < sz(left); i++) {
            query[left[i].first] = left[i + 1].first;
        }
        string res = doquery(query);
        vector<pii> nleft;
        for (int i = 0; i < sz(left); i++) {
            pii cur = left[i];
            while (i + 1 < sz(left) && res[left[i].first] == '1') {
                cur.second += left[i + 1].second;
                ++i;
            } 
            nleft.push_back(cur);
        }
        for (int i = 0; i + 1 < sz(nleft); i++) {
            int rem = min(nleft[i].second, nleft[i + 1].second);
            nleft[i].second -= rem;
            nleft[i + 1].second -= rem;
        }
        left.clear();
        trav(it, nleft) if (it.second) left.push_back(it);
    }
    if (left.empty())
        cout << "! -1" << endl;
    else {
        vi lastcount(N, left[0].first);
        string res = doquery(lastcount);
        int match = count(all(res), '1');
        if (match * 2 > N)
            cout << "! " << (left[0].first+1) << endl;
        else
            cout << "! -1" << endl;
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
