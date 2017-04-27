#! /bin/bash
old_i=100
for i in 100 150 200 250 300 350 400
do
  sed -i "s/MD_TIMEOUT = $old_i/MD_TIMEOUT = $i/g" controller.hh
  make
  ./run-contest warmup &> output_c/timeout_${i}.out
  old_i=$i
done
