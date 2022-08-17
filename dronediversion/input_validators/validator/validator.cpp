#include "validator.h"

bool twolines(vector<int> xs) {
    sort(all(xs));
    assert(xs[0] == xs[1]);
    assert(xs[1] != xs[2]);
    assert(xs[2] == xs[3]);
}

void run() {
    int W = Int(2, Arg("W")); Space();
    int H = Int(2, Arg("H")); Endl();

    int xs1 = Int(0, W - 1); Space();
    int ys1 = Int(0, H - 1); Space();
    int xd1 = Int(0, W - 1); Space();
    int yd1 = Int(0, H - 1); Endl();

    int xs2 = Int(0, W - 1); Space();
    int ys2 = Int(0, H - 1); Space();
    int xd2 = Int(0, W - 1); Space();
    int yd2 = Int(0, H - 1); Endl();

    // Start != destination
    assert(xs1 != xd1 || ys1 != yd1);
    assert(xs2 != xd2 || ys2 != yd2);
    // Different starting positions
    assert(xs1 != xs2 || ys1 != ys2);

    if (Arg("rectangle", 0)) {
        assert(twolines({xs1, xd1, xs2, xd2}));
        assert(twolines({ys1, yd1, ys2, yd2}));
        set<pii> ps;
        ps.emplace(xs1, ys1);
        ps.emplace(xs2, ys2);
        ps.emplace(xd1, yd1);
        ps.emplace(xd2, yd2);
        assert(ps.size() == 4);
    }

    if (Arg("x0", 0)) {
        assert(xs1 == 0);
        assert(xd1 == 0);
        assert(xs2 == 0);
        assert(xd2 == 0);
    }

    if (Arg("twolines", 0)) {
        assert(xs1 == xd1);
        assert(ys2 == yd2);
    }

	int n = Int(1, Arg("n"));
	Space();
	int m = Int(1, Arg("m"));
	Space();
	int k = Int(1, Arg("k"));
	Endl();

	bool require_connected = Arg("connected", 0);

	vector<int> colors = SpacedInts(n, 1, k);

	vector<vector<int>> ed(n);
	for (int i = 0; i < m; i++) {
		int a = Int(1, n);
		Space();
		int b = Int(1, n);
		Endl();
		assert(a != b);
		ed[a-1].push_back(b-1);
		ed[b-1].push_back(a-1);
	}

	for (int i = 0; i < n; i++) {
		assert(set<int>(ed[i].begin(), ed[i].end()).size() == ed[i].size());
	}

	if (require_connected) {
		vector<int> stack = {0}, seen(n);
		while (!stack.empty()) {
			int x = stack.back(); stack.pop_back();
			if (seen[x]++) continue;
			for (int y : ed[x]) stack.push_back(y);
		}
		assert(count(seen.begin(), seen.end(), 0) == 0);
	}
}
