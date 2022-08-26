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
    while (sz(left) > 2) {
        vector<int> query(N, 1);
        for (int i = 0; i + 2 < sz(left); i += 3) {
            query[left[i].first] = left[i + 1].first;
            query[left[i + 1].first] = left[i + 2].first;
            query[left[i + 2].first] = left[i].first;
        }
        string res = doquery(query);
        vector<pii> nleft;
        for (int i = 0; i + 2 < sz(left); i += 3) {
            vector<pii> qs = {left[i]};
            if (res[left[i].first] == '1') {
                qs.back().second += left[i + 1].second;
            } else {
                qs.push_back(left[i + 1]);
            }
            if (res[left[i + 2].first] == '1') {
                qs.front().second += left[i + 2].second;
            } else if (res[left[i + 1].first] == '1') {
                qs.back().second += left[i + 2].second;
            } else {
                qs.push_back(left[i + 2]);
            }
            
            if (qs.size() >= 2) {
                int rem = min(qs[0].second, qs[1].second);
                qs[0].second -= rem;
                qs[1].second -= rem;
            }
            if (qs.size() >= 3) {
                int rem1 = min(qs[0].second, qs[2].second);
                qs[0].second -= rem1;
                qs[2].second -= rem1;
                int rem2 = min(qs[1].second, qs[2].second);
                qs[1].second -= rem2;
                qs[2].second -= rem2;
            }
            trav(it, qs) if (it.second) nleft.push_back(it); 
        }
        if (sz(left) % 3 >= 1) nleft.push_back(left[sz(left) - 1]);
        if (sz(left) % 3 >= 2) nleft.push_back(left[sz(left) - 2]);
        left.swap(nleft);
    }
    for (int i = 0; i < sz(left); i++) {
        vi lastcount(N, left[i].first);
        string res = doquery(lastcount);
        int match = count(all(res), '1');
        if (match * 2 > N) {
            cout << "! " << (left[i].first+1) << endl;
            return;
        }
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
