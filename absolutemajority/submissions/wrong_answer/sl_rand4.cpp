#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	const int Q = 3;
	int N;
	cin >> N;
	assert(cin);
	vector<pii> unequalv;
	UF uf(N);
	rep(qi,0,Q-1) {
		vi target(N);
		rep(i,0,N) target[i] = rand() % N;
		cout << "? ";
		rep(i,0,N) cout << target[i]+1 << ' ';
		cout << endl;
		string res;
		cin >> res;
		assert(cin);
		rep(i,0,N) {
			if (res[i] == '1') uf.join(i, target[i]);
			else unequalv.push_back({i, target[i]});
		}
	}

	// Less fancy algorithm to do the last query.
	// We split component sizes > N/3 vs < N/3 and assume the majority falls within the former case.
	// N/4 would also work but is a little more complex.

	vector<vi> compNodes(N);
	rep(i,0,N) compNodes[uf.find(i)].push_back(i);

	vi big, small, compSizes;
	rep(i,0,N) if (uf.find(i) == i) {
		int s = uf.size(i);
		compSizes.push_back(s);
		if (uf.size(i) > N/3)
			big.push_back(i);
		else
			small.push_back(i);
	}
	assert(sz(big) <= 2);
	sort(all(compSizes), greater<int>());

	vi target(N, -1);
	if (sz(big) <= 1) {
		int x = big.empty() ? 0 : big[0];
		rep(i,0,N) target[i] = x;
	} else {
		rep(bigi,0,2) {
			int i = big[bigi], nonI = big[!bigi];
			// < N/3 vs > N/3
			assert(sz(small) < sz(compNodes[i]));
			rep(j,0,sz(small))
				target[compNodes[i][j]] = small[j];
			target[compNodes[i].back()] = nonI;
		}
	}

	cout << "? ";
	rep(i,0,N) if (target[i] == -1) target[i] = 0;
	rep(i,0,N) cout << target[i] + 1 << ' ';
	cout << endl;
	string res;
	cin >> res;
	assert(cin);
	rep(i,0,N) if (res[i] == '1') uf.join(i, target[i]);
	int maxSize = -1, maxInd = -1;
	rep(i,0,N) if (uf.find(i) == i) {
		int s = uf.size(i);
		if (s > maxSize) {
			maxSize = s;
			maxInd = i;
		}
	}
	cerr << "Max size: " << maxSize << " / " << N << " (comps: " << compSizes[0];
	rep(i,1,min(4, sz(compSizes))) cerr << ", " << compSizes[i];
	cerr << ")" << endl;
	if (maxSize > N/2)
		cout << "! " << maxInd+1 << endl;
	else
		cout << "! " << -1 << endl;
	return 0;
}
