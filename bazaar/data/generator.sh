#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution js.cpp

compile gen_01.py
compile gen_10.py
compile gen_alt.py
compile gen_alt2.py
compile gen_random.py

samplegroup
sample 1
sample 2

group group1 1
limits 2n=10

tc 1
tc 2
tc 01-small gen_01 n=5
tc 10-small gen_10 n=5
tc alt-small gen_alt n=5
tc alt2-small gen_alt2 n=5
tc rand1-small gen_random n=5
tc rand2-small gen_random n=5
tc rand3-small gen_random n=5
tc rand4-small gen_random n=5

group group2 1
limits 2n=2000
include_group group1

tc 01-mid gen_01 n=1000
tc 10-mid gen_10 n=1000
tc alt-mid gen_alt n=1000
tc alt2-mid gen_alt2 n=1000
tc rand1-mid gen_random n=1000
tc rand2-mid gen_random n=1000
tc rand3-mid gen_random n=1000
tc rand4-mid gen_random n=1000

group group3 1
limits 2n=100000
include_group group2

tc 01-big gen_01 n=50000
tc 10-big gen_10 n=50000
tc alt-big gen_alt n=50000
tc alt2-big gen_alt2 n=50000
tc rand1-big gen_random n=50000
tc rand2-big gen_random n=50000
tc rand3-big gen_random n=50000
tc rand4-big gen_random n=50000
