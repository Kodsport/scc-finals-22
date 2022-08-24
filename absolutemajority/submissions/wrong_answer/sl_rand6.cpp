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

int main() {
	cin.tie(0)->sync_with_stdio(0);
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

	// Less fancy (but still slightly fancy) algorithm to do the last query.
	// We split component sizes > N/4 vs < N/4 and assume the majority falls within the former case.

	vector<vi> compNodes(N);
	rep(i,0,N) compNodes[uf.find(i)].push_back(i);

	vi big, small, compSizes;
	rep(i,0,N) if (uf.find(i) == i) {
		int s = uf.size(i);
		compSizes.push_back(s);
		if (uf.size(i) > N/4)
			big.push_back(i);
		else
			small.push_back(i);
	}
	assert(sz(big) <= 3);
	sort(all(compSizes), greater<int>());

	vi target(N, -1);
	if (sz(big) <= 1) {
		int x = big.empty() ? 0 : big[0];
		rep(i,0,N) target[i] = x;
	} else if (sz(big) == 2) {
		target.assign(N, -1);
		vi compA = compNodes[big[0]];
		vi compB = compNodes[big[1]];
		rep(i,0,sz(small)) {
			if (i < sz(compA))
				target[compA[i]] = small[i];
			else
				target[small[i]] = big[0];
		}
		// < N/2 vs > N/2
		assert(sz(small) < sz(compA) + sz(compB));
		rep(i,0,sz(small)) {
			if (i < sz(compA))
				target[small[i]] = big[1];
			else
				target[compB[i - sz(compA)]] = small[i];
		}
		assert(target[compB.back()] == -1);
		target[compB.back()] = big[0];
	} else {
		assert(sz(big) == 3);
		rep(bigi,0,3) {
			int i = big[bigi], i2 = big[(bigi + 1) % 3];
			// < N/4 vs > N/4
			assert(sz(small) < sz(compNodes[i]));
			rep(j,0,sz(small))
				target[compNodes[i][j]] = small[j];
			target[compNodes[i].back()] = i2;
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
