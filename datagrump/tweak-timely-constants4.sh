#! /bin/bash
old_i=0.1
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
do
  sed -i "s/DELTA = $old_i/DELTA = $i/g" controller.hh
  make
  ./run-contest warmup &> output_contest/DELTA_${i}.out
  old_i=$i
done
