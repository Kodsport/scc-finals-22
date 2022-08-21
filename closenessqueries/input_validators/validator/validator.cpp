#include "validator.h"

void run() {
    int N = Int(Arg("n", 45000), 45000); Space();
    int M = Int(Arg("m", 200000), 200000); Endl();

    set<pair<int, int>> ed;
    for (int i = 0; i < M; i++) {
        int a = Int(0, N - 1); Space();
        int b = Int(0, N - 1); Endl();

        assert(a != b);
        assert(ed.count(make_pair(a, b)) == 0);
        ed.insert(make_pair(a, b));
        ed.insert(make_pair(b, a));
    }


    int Q = Int(1, Arg("q", 10000)); Endl();
    for (int i = 0; i < Q; i++) {
        int a = Int(0, N - 1); Space();
        int b = Int(0, N - 1); Endl();

        assert(a != b);
    }
    Eof();
}
