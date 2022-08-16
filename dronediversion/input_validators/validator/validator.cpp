#include "validator.h"

void run() {
    int Q = Int(1, Arg("q")); Endl();
    for (int q = 0; q < Q; ++q) {
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

    }
    Eof();
}
