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

struct Node {
	Node *left = 0, *right = 0;
	int lazyMin = inf, theMin = 0;
	int size;
	Node(int size) : size(size) {
		if (size > 1) {
			int mid = size / 2;
			left = new Node(mid);
			right = new Node(size - mid);
		} else {
			assert(size == 1);
		}
	}
	int getMin() { return theMin; }
	void setMin(int v) {
		theMin = min(theMin, v);
		lazyMin = min(lazyMin, v);
	}
	int getInd(int ind) {
		assert(0 <= ind && ind < size);
		if (size == 1) return theMin;
		push();
		int mid = size/2;
		if (ind < mid) return left->getInd(ind);
		else return right->getInd(ind - mid);
	}
	void setInd(int ind, int v) {
		assert(0 <= ind && ind < size);
		if (size == 1) {
			theMin = v;
			return;
		}
		push();
		int mid = size/2;
		if (ind < mid) {
			left->setInd(ind, v);
		}
		else {
			right->setInd(ind - mid, v);
		}
		theMin = min(left->theMin, right->theMin);
	}
	void push() {
		if (lazyMin != inf) {
			left->lazyMin = min(left->lazyMin, lazyMin);
			left->theMin = min(left->theMin, lazyMin);
			right->lazyMin = min(right->lazyMin, lazyMin);
			right->theMin = min(right->theMin, lazyMin);
			lazyMin = inf;
		}
	}
};

int A;
vector<vi> ed;
vi nch;
vi pars, chind;
vi startDists;
void dfs(int at, int dist, int par = -1) {
	if (at == A) dist = inf;
	startDists[at] = min(dist, inf);
	pars[at] = par;
	int ind = 0;
	trav(x, ed[at]) if (x != par) {
		nch[at]++;
		chind[x] = ind++;
		dfs(x, dist + 1, at);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, M;
	cin >> N >> M;
	int B;
    A = 0, B = 1;
	ed.resize(N+1);
	rep(i,0,N-1) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].push_back(b);
		ed[b].push_back(a);
	}
	int root = B;
	ed[N].push_back(root);
	ed[root].push_back(N);

	nch.resize(N+1);
	pars.resize(N+1, -2);
	chind.resize(N+1);
	startDists.resize(N+1);
	dfs(N, -1);

	rep(i,0,N) assert(pars[i] != -2);
	rep(i,0,N) assert(pars[i] != i);

	vector<Node*> chs(N+1);
	rep(i,0,N+1) {
		if (nch[i]) chs[i] = new Node(nch[i]);
	}

	auto getval = [&](int x) {
		assert(x != N);
		int p = pars[x];
		return chs[p]->getInd(chind[x]);
	};
	auto setval = [&](int x, int v) {
		assert(x != N);
		int p = pars[x];
		assert(chs[p]);
		chs[p]->setInd(chind[x], v);
	};

	int last = A;
	rep(i,0,N) setval(i, startDists[i]);

	rep(qi,0,M) {
		int a;
		cin >> a;
		--a;
		int v = getval(a);
		if (chs[a]) chs[a]->setMin(v + 1);
		if (a != root) {
			int p = pars[a];
			setval(p, min(getval(p), v + 1));
		}
		setval(a, inf);
		v = inf;
		if (chs[last]) v = chs[last]->getMin();
		if (last != root) {
			int p = pars[last];
			v = min(v, getval(p));
		}
		setval(last, v + 1);
		last = a;
	}
	int res = inf;
	rep(i,0,N) res = min(res, getval(i));
	if (res >= inf) {
		cout << -1 << endl;
	} else {
		cout << res << endl;
	}
	exit(0);
}
