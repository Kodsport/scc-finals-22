#include "validator.h"

void run() {
    int TN = Int(1, Arg("2n", 100000)); Endl();
    assert(TN % 2 == 0);
    int N = TN / 2;

    vector<int> A = SpacedInts(N, 1, TN);
    vector<int> B = SpacedInts(N, 1, TN);
    set<int> Q;
    Q.insert(A.begin(), A.end());
    Q.insert(B.begin(), B.end());
    assert(Q.size() == TN);
    Eof();
}
