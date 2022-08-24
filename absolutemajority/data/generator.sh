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
tc big-twoway2 n=99999 s=50000,49999 order=rtl
tc big-twoway3 n=65536 s=32769,32760 order=bitrev
tc big-twoway4 n=99997 s=49999,49985 order=ltr
tc big-twoway-nomaj2 n=100000 s=50000,50000
tc big-allsame n=1e5 s=100000
tc big-many-unique n=100000 s=50001
tc big-many-unique2 n=65536 s=32769 order=bitrev
tc big-many-unique-nomaj n=100000 s=49999
tc big-threesplit n=100000 s=33333,33333,33333
tc big-threeway n=100000 s=50001,25000,24999
tc big-fourway n=100000 s=50001,16666,16666,16666
tc big-fiveway n=100000 s=50001,12500,12500,12499,12499
tc big-fiveway-nomaj n=100000 s=49999,12500,12500,12499,12499

tc five-nomaj n=5 s=2
tc five-nomaj2 n=5 s=2,2
tc five-1 mode=fixed s=1,1,1,2,3
tc five-2 mode=fixed s=1,1,2,1,3
tc five-3 mode=fixed s=1,2,1,2,3
tc five-4 mode=fixed s=2,1,1,1,3
tc five-5 mode=fixed s=1,1,2,3,1
tc five-6 mode=fixed s=1,2,1,3,1
tc five-7 mode=fixed s=2,1,1,3,1
tc five-8 mode=fixed s=1,2,3,1,1
tc five-9 mode=fixed s=2,1,3,1,1
tc five-10 mode=fixed s=2,3,1,1,1
