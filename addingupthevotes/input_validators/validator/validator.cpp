#include "validator.h"

void run() {
    int T = Int(1, 10'000); Endl();
    long long sumN = 0;
    for (int i = 0; i < T; i++) {
        int N = Int(1, 100'000);
        sumN += N;
        Endl();
        SpacedInts(N, 0, INT_MAX);
    }
    assert(sumN <= 100'000);
}
