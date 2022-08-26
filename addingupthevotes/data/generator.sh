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

tc one n=1 s=1
tc big-twoway1 n=100000 s=50001,49999
tc big-twoway-nomaj1 n=100000 s=49999,49998

# Randomized solutions can have problems with small cases
tc five-nomaj n=5 s=2
tc five-nomaj2 n=5 s=2,2
tc five-1 mode=fixed s=1,1,1,2,3
tc five-2 mode=fixed s=1,1,2,1,3
tc five-3 mode=fixed s=1,2,1,1,3
tc five-4 mode=fixed s=2,1,1,1,3
tc five-5 mode=fixed s=1,1,2,3,1
tc five-6 mode=fixed s=1,2,1,3,1
tc five-7 mode=fixed s=2,1,1,3,1
tc five-8 mode=fixed s=1,2,3,1,1
tc five-9 mode=fixed s=2,1,3,1,1
tc five-10 mode=fixed s=2,3,1,1,1
tc seven-many-unique1 n=7 s=4
tc seven-many-unique2 n=7 s=4
tc seven-close1 n=7 s=4,2
tc seven-close2 n=7 s=4,3
tc seven-close3 n=7 s=4,3
tc nine-many-unique n=9 s=5
tc nine-close1 n=9 s=5,4
tc nine-close2 n=9 s=5,4
tc eleven-close1 n=11 s=6,5
tc eleven-close2 n=11 s=6,5
tc eleven-many-unique n=11 s=6
for A in {1..10}; do
  tc small-close1-$A n=$((A*2+11)) s=$((A+6)),$((A+5))
  tc small-close2-$A n=$((A*2+41)) s=$((A+21)),$((A+20))
done
tc three n=3 s=2
tc three-nomaj n=3 s=1

tc med-close-1 n=100 s=51,49
tc med-close-2 n=1000 s=501,499
tc med-close-3 n=10000 s=5001,4999

# Deterministic solutions can have problems with large cases
tc big-twoway2 n=99999 s=50000,49999 order=rtl
tc big-twoway3 n=65536 s=32769,32760 order=bitrev
tc big-twoway4 n=99997 s=49999,49985 order=ltr
tc big-twoway-nomaj2 n=100000 s=50000,50000
tc big-allsame n=1e5 s=100000
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

tc small-close-many-00 n=11 s=6,5 times=MAX
tc small-close-many-01 n=21 s=11,10 times=MAX
tc small-close-many-02 n=31 s=16,15 times=MAX
tc small-close-many-03 n=51 s=26,25 times=MAX
tc small-close-many-04 n=71 s=36,35 times=MAX
tc med-many-unique n=1000 s=501 times=MAX
tc small-many-unique-1 n=100 s=51 times=MAX
tc small-many-unique-2 n=99 s=50 times=MAX
tc med-close-many-00 n=100 s=51,49 times=MAX
tc med-close-many-01 n=201 s=101,100 times=MAX
tc med-close-many-02 n=300 s=151,149 times=MAX
tc med-close-many-03 n=501 s=250,249 times=MAX
tc med-close-many-04 n=700 s=351,349 times=MAX
tc med-close-many-05 n=900 s=451,449 times=MAX
tc med-close-many-06 n=1000 s=501,499 times=MAX
tc med-close-many-07 n=3001 s=1500,1499 times=MAX
tc med-close-many-08 n=7000 s=3501,3499 times=MAX
tc med-close-many-09 n=9999 s=5000,4999 times=MAX
tc med-close-many-10 n=10000 s=5001,4999 times=MAX
tc big-twoway-many-1 n=99999 s=50000,49999
tc big-twoway-many-2 n=100000 s=50001,49999
