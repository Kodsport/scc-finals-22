#!/bin/bash
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution sl_mlogn.cpp opt

compile gen_random.py
compile gen_bigans.py
compile gen_alt.py

samplegroup
limits n=100 m=500
sample 1
sample 2

group group1 23
limits n=100 m=500

tc 1
tc 2
tc small-smalldeg-rand-drunk gen_random n=100 m=500 deg=3 mode=random walk=drunk
tc small-line-drunk gen_random n=100 m=500 deg=3 mode=line walk=drunk
tc small-tinystar gen_random n=4 m=500 mode=star walk=drunk
tc small-small1-drunk gen_random n=7 m=500 deg=3 mode=random walk=drunk
tc small-small2-drunk gen_random n=8 m=500 mode=random walk=drunk
tc small-small3-drunk gen_random n=8 m=500 mode=random walk=drunk
tc small-small4-drunk gen_random n=6 m=500 deg=3 mode=random walk=drunk
tc small-rand-tour gen_random n=80 m=500 mode=random walk=tour chaos=40

group group2 27
limits n=100000 m=500000 deg=3

tc 1
tc 2
tc small-smalldeg-rand-drunk
tc small-line-drunk
tc small-small1-drunk
tc small-small4-drunk
tc smalldeg-line-imp1 gen_random n=100000 m=500000 mode=line walk=tour chaos=10000 monsterstart=0
tc smalldeg-line-imp2 gen_random n=100000 m=500000 mode=line walk=tour chaos=100000
tc smalldeg-rand-drunk gen_random n=100000 m=500000 deg=3 mode=random walk=drunk
tc smalldeg-deep-tour gen_random n=100000 m=500000 deg=3 mode=deep walk=tour chaos=20000
tc smalldeg-deeper-tour gen_random n=100000 m=500000 deg=3 mode=deeper walk=tour chaos=20000
tc smalldeg-line-drunk gen_random n=100000 m=500000 deg=3 mode=line walk=drunk
tc smalldeg-tinystar gen_bigans n=4 m=500000
tc smalldeg-bigans gen_bigans n=100000 m=500000
tc smalldeg-smalln-drunk gen_random n=10 m=500000 deg=3 mode=random walk=drunk
tc smalldeg-rand-tour gen_random n=100000 m=500000 deg=3 mode=random walk=tour chaos=100000

group group3 50
limits n=100000 m=500000
include_group group1
include_group group2

tc large-rand-drunk gen_random n=100000 m=500000 mode=random walk=drunk
tc large-star-drunk gen_random n=100000 m=500000 mode=star walk=drunk
tc large-smalln-drunk gen_random n=10 m=500000 mode=random walk=drunk
tc large-alt gen_alt n=100000 m=500000
tc large-shallower-tour gen_random n=100000 m=500000 mode=shallower walk=tour chaos=20000
tc large-twostar-drunk gen_random n=100000 m=500000 mode=twostar walk=drunk
tc large-twostar-tour gen_random n=100000 m=500000 mode=twostar walk=tour chaos=10000
tc large-rand-tour gen_random n=100000 m=500000 mode=random walk=tour chaos=100000
tc large-deeper-tour gen_random n=100000 m=500000 mode=deeper walk=tour chaos=20000
tc large-smalln-rand-tour gen_random n=1000 m=500000 mode=random walk=tour chaos=500
tc large-smallstar gen_random n=500 m=500000 mode=star walk=tour chaos=100
tc large-smallalmoststar gen_random n=500 m=500000 mode=almoststar walk=tour chaos=100
tc large-smallalmoststarsomeskips gen_random n=500 m=500000 mode=almoststar walk=tour chaos=100 skips=1
tc large-twostar-alternate gen_random n=100000 m=500000 mode=twostar walk=twostarrand
