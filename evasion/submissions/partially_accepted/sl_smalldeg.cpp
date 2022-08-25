#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int inf = 1'000'000'000;

int N;
vi dp;
vector<vi> ed;

void dfs(int x, int dist = 0, int par = -1) {
	if (dp[x] == inf) dist = inf;
	dp[x] = min(dist, inf);
	trav(y, ed[x]) if (y != par) {
		dfs(y, dist + 1, x);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, M;
	cin >> N >> M;
	int A, B;
	cin >> A >> B;
	--A, --B;
	ed.resize(N);
	rep(i,0,N-1) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].push_back(b);
		ed[b].push_back(a);
	}
	dp.assign(N, 0);
	dp[A] = inf;
	dfs(B);
	assert(dp[A] == inf);
	int last = A;
	rep(qi,0,M) {
		int a;
		cin >> a;
		--a;
		int v = dp[a];
		trav(e, ed[a]) {
			dp[e] = min(dp[e], v + 1);
		}
		dp[a] = inf;
		v = inf;
		trav(e, ed[last]) {
			v = min(v, dp[e] + 1);
		}
		dp[last] = v;
		last = a;
	}
	int res = *min_element(all(dp));
	if (res >= inf) {
		cout << -1 << endl;
	} else {
		cout << res << endl;
	}
}
