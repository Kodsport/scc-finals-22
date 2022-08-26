#!/bin/bash
TC_INDEX=1
tc() {
  local name="$1"
  local path="secret/$(printf '%03d' $TC_INDEX)-$name"
  let TC_INDEX++
  seed=$((16#$(echo -n "$name" | md5sum | head -c 6)))
  echo python3 gen_random.py "${@:2}" $seed ">$path.in"
  python3 gen_random.py "${@:2}" $seed >$path.in
  >$path.ans
}

rm -f secret/*.in secret/*.ans

tc big-twoway1 n=100000 s=50001,49999
tc big-twoway-nomaj1 n=100000 s=49999,49998

# Randomized solutions can have problems with small cases
tc tiny n=1 maxn=7 s=rand times=MAX
tc small n=7 maxn=30 s=rand times=MAX
tc small-many-unique n=7 maxn=23 s=onebig times=MAX
for A in {1..10}; do
  tc small0-close-$A n=5 maxn=13 s=close times=MAX
done
for A in {1..15}; do
  tc small1-close-$A n=14 maxn=25 s=close times=MAX
done
for A in {1..10}; do
  tc small2-close-$A n=26 maxn=40 s=close times=MAX
done
for A in {1..10}; do
  tc small3-close-$A n=41 maxn=100 s=close times=MAX
done

# Deterministic solutions can have problems with large cases
tc big-twoway2 n=99999 s=50000,49999 order=rtl
tc big-twoway3 n=65536 s=32769,32760 order=bitrev
tc big-twoway4 n=99997 s=49999,49985 order=ltr
tc big-twoway-nomaj2 n=100000 s=50000,50000
tc big-allsame n=100000 s=100000
tc big-all-unique n=100000 s=1
tc big-many-unique-1 n=10000 s=5001 times=MAX
tc big-many-unique-2 n=10000 s=5001 times=MAX
tc big-many-unique-3 n=10000 s=5001 times=MAX
tc big-many-unique-4 n=65536 s=32769 order=bitrev
tc big-many-unique-nomaj n=100000 s=49999
tc big-threesplit n=100000 s=33333,33333,33333
tc big-threeway n=100000 s=50001,25000,24999
tc big-fourway n=100000 s=50001,16666,16666,16666
tc big-fiveway n=100000 s=50001,12500,12500,12499,12499
tc big-fiveway-nomaj n=100000 s=49999,12500,12500,12499,12499

tc small-many-unique-1 n=20 maxn=100 s=onebig times=MAX
tc med-many-unique n=500 maxn=2000 s=501 times=MAX
tc med-close-many-00 n=90 maxn=1100 s=close times=MAX
tc med-close-many-01 n=90 maxn=1100 s=close times=MAX
tc med-close-many-02 n=90 maxn=1100 s=close times=MAX
tc med-close-many-03 n=2000 maxn=7000 s=close times=MAX
tc med-close-many-04 n=10000 s=close times=MAX
