#! /bin/bash
old_i=0.1
old_j=0.1
for i in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
do
  sed -i "s/ALPHA = $old_i/ALPHA = $i/g" controller.hh
  for j in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9
  do
    sed -i "s/BETA = $old_j/BETA = $j/g" controller.hh
    make
    ./run-contest warmup &> output_contest/ALPHA_${i}_BETA_${j}.out
    old_j=$j
  done
  old_i=$i
done
