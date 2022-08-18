#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution js.cpp

compile gen_random.py
compile gen_random_cross.py
compile gen_random_sameline.py
compile gen_exhaustive.py
compile gen_exhaustive_cross.py


samplegroup
sample 1

# $1$    & $??$        &  $x_{s_1} = x_{d_1}$ and $y_{s_2} = y_{d_2}$ \\ \hline
group group1 1
limits twolines=1

tc all-crosses-7x7 gen_exhaustive_cross w=7 h=7
tc random-cross-100k gen_random_cross
tc random-cross-small-100k gen_random_cross w=300 h=300
tc random-cross-elongated-100k gen_random_cross w=300 h=10000
tc random-cross-mid-100k gen_random_cross w=10000 h=10000

# $2$    & $??$        &  $W = 1$ \\ \hline
group group2 1
limits w=1

tc all-1x30 gen_exhaustive w=1 h=30
tc random-sameline-100k gen_random_sameline
tc random-sameline-small-100k gen_random_sameline w=300
tc random-sameline-mid-100k gen_random_sameline w=10000

# $3$    & $??$        &  $W, H \le 50$, $Q \le 150$ \\ \hline
group group3 1
limits w=50 h=50 q=150

tc 1
tc all-2x2 gen_exhaustive w=2 h=2
tc all-crosses-3x2 gen_exhaustive_cross w=3 h=2
tc all-crosses-2x3 gen_exhaustive_cross w=2 h=3
tc random-sameline-small1 gen_random_sameline q=150 h=50
tc random-sameline-small2 gen_random_sameline q=150 h=50
tc random-cross-tiny gen_random_cross q=150 h=10 w=10
tc random-cross-small gen_random_cross q=150 h=50 w=50
tc random-10x10 gen_random q=150 w=10 h=10
tc random-50x50 gen_random q=150 w=50 h=50

# $4$    & $??$        &  $W, H \le 1\,000$, $Q \le 1000$ \\ \hline
group group4 1
limits w=1000 h=1000 q=1000
include_group group3

tc all-3x2 gen_exhaustive w=3 h=2
tc all-3x3 gen_exhaustive w=2 h=3
tc random-sameline-mid1 gen_random_sameline q=1000 h=1000
tc random-sameline-mid2 gen_random_sameline q=1000 h=1000
tc random-cross-mid1 gen_random_cross q=1000 h=100 w=100
tc random-cross-mid2 gen_random_cross q=1000 h=1000 w=1000
tc random-100x100 gen_random q=1000 w=100 h=100
tc random-500x500 gen_random q=1000 w=500 h=500
tc random-1000x1000 gen_random q=1000 w=1000 h=1000

# $5$    & $??$        &  No additional constraints \\ \hline
group group5 1
include_group group1
include_group group2
include_group group3
include_group group4

tc all-4x5 gen_exhaustive w=4 h=5
tc random-50x50-100k gen_random q=100000 w=50 h=50
tc random-500x500-100k gen_random q=100000 w=500 h=500
tc random-1000x1000-100k gen_random q=100000 w=1000 h=1000
tc random-100000x100000-100k gen_random q=100000 w=100000 h=100000
tc random-100k-1 gen_random q=100000
tc random-100k-2 gen_random q=100000
