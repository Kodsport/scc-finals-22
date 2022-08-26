// Like sl_rand1 but the query graph for each of the first Q-1 queries is regular.
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

default_random_engine rng(2);

vi genRegular(int N) {
	// Generates a uniformly random 2-regular graph, possibly with
	// loops/duplicate edges, and directs it.
	vi ret(N, -1);
	vi count(N);
	vi ends(2*N);
	rep(i,0,N) ends[2*i] = ends[2*i+1] = i;
	shuffle(all(ends), rng);
	vi xors(N);
	rep(i,0,N) {
		int a = ends[2*i], b = ends[2*i+1];
		xors[a] ^= b;
		xors[b] ^= a;
	}
	rep(i,0,N) {
		int a = ends[2*i], b = ends[2*i+1];
		if (ret[a] != -1) continue;
		ret[a] = b;
		xors[a] ^= b;
		xors[b] ^= a;
		while (ret[b] == -1) {
			a = b;
			b = xors[a];
			xors[b] ^= a;
			xors[a] ^= b;
			ret[a] = b;
		}
	}
	vi ins(N);
	rep(i,0,N) {
		assert(xors[i] == 0);
		assert(ret[i] >= 0 && ret[i] < N);
		ins[ret[i]]++;
	}
	rep(i,0,N) assert(ins[i] == 1);
	return ret;
}

void solve() {
	const int Q = 3;
	int N;
	cin >> N;
	assert(cin);
	vector<pii> unequalv;
	UF uf(N);
	rep(qi,0,Q-1) {
		vi target = genRegular(N);
		rep(it,0,10) {
			rep(i,0,N) if (target[target[i]] == i) goto bad;
			break;
bad:
			target = genRegular(N);
		}
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

	// Fancy algorithm to do the last query ~optimally

	set<pii> unequal;
	trav(pa, unequalv) {
		int a = uf.find(pa.first);
		int b = uf.find(pa.second);
		unequal.insert({a, b});
		unequal.insert({b, a});
	}

	vector<vi> compNodes(N);
	vi comps, compSizes;
	rep(i,0,N) compNodes[uf.find(i)].push_back(i);
	rep(i,0,N) if (uf.find(i) == i) comps.push_back(i), compSizes.push_back(uf.size(i));
	sort(all(comps), [&](int a, int b) { return uf.size(a) < uf.size(b); });
	sort(all(compSizes), greater<int>());

	vi target(N, -1);
	for (int i = sz(comps)-1; i >= 0; i--) {
		int comp = comps[i];
		vi& nodes = compNodes[comp];
		int j = 0;
		while (j < i) {
			int jcomp = comps[j];
			if (unequal.count({comp, jcomp})) {
				j++;
				continue;
			}
			if (nodes.empty()) break;
			int x = nodes.back();
			nodes.pop_back();
			target[x] = jcomp;
			j++;
		}
		if (j < i) {
			if (compNodes[comps[j]].empty()) break;
			while (j < i) {
				int jcomp = comps[j];
				if (unequal.count({comp, jcomp})) {
					j++;
					continue;
				}
				auto& jnodes = compNodes[jcomp];
				assert(!jnodes.empty());
				int x = jnodes.back();
				jnodes.pop_back();
				target[x] = comp;
				j++;
			}
			sort(comps.begin(), comps.begin() + i, [&](int a, int b) {
				return sz(compNodes[a]) < sz(compNodes[b]);
			});
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
