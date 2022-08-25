#include "validator.h"

struct UF {
	vector<int> e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		assert(a >= 0 && b >= 0);
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

void run() {
    int N = Int(2, Arg("n")); Space();
    int M = Int(1, Arg("m")); Endl();

	UF uf(N);

	set<pair<int, int>> ed;
	vector<int> deg(N);
    for (int i = 0; i < N-1; i++) {
        int a = Int(1, N); Space();
        int b = Int(1, N); Endl();
        --a; --b;
		assert(uf.join(a, b));
		ed.insert({a, b});
		ed.insert({b, a});
		deg[a]++;
		deg[b]++;
    }

	int maxDeg = Arg("deg", N);
	for (int i = 0; i < N; i++) {
		assert(deg[i] <= maxDeg);
	}

	int prev = 0;
	vector<int> moves = SpacedInts(M, 1, N);
	for (int i = 0; i < M; i++) {
        --moves[i];
		assert(ed.count({prev, moves[i]}));
		prev = moves[i];
	}
}
