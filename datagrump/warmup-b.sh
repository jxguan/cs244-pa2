#! /bin/bash
old_i=1
old_j=0.2
for i in 1 2 4 8 16
do
  sed -i "s/INCREASE_SIZE = $old_i/INCREASE_SIZE = $i/g" controller.hh
  for j in 0.2 0.4 0.6 0.8
  do
    sed -i "s/DECREASE_FACTOR = $old_j/DECREASE_FACTOR = $j/g" controller.hh
    make
    ./run-contest warmup &> output_b/AI_${i}_MD_${j}.out
    old_j=$j
  done
  old_i=$i
done
