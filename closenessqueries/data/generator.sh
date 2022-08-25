#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../testdata_tools/gen.sh

use_solution js.cpp opt

compile gen_graph.py

samplegroup
limits n=1 m=1
sample 1

group group1 10
limits q=1

tc q1-01 gen_graph q=1
tc q1-02 gen_graph q=1
tc q1-03 gen_graph q=1
tc q1-04 gen_graph q=1
tc q1-05 gen_graph q=1
tc q1-06 gen_graph q=1
tc q1-07 gen_graph q=1
tc q1-08 gen_graph q=1
tc q1-09 gen_graph q=1
tc q1-10 gen_graph q=1

group group2 40

tc qb-01 gen_graph
tc qb-02 gen_graph
tc qb-03 gen_graph
tc qb-04 gen_graph
tc qb-05 gen_graph
tc qb-06 gen_graph
tc qb-07 gen_graph
tc qb-08 gen_graph
tc qb-09 gen_graph
tc qb-10 gen_graph
