#! /bin/bash
old_j=40
old_k=100
for j in 40 60 80 100
do
  sed -i "s/T_LOW = $old_j/T_LOW = $j/g" controller.hh
  for k in 100 150 200 250
  do
    sed -i "s/T_HIGH = $old_k/T_HIGH = $k/g" controller.hh
    make
    ./run-contest warmup &> output_contest/LOW_${j}_HIGH_${k}.out
    old_k=$k
  done
  old_j=$j
done
