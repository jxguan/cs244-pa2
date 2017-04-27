#! /bin/bash
old_i=1
for i in 1 2 5 10 20 50 100
do
  sed -i "s/INITIAL_WINDOW_SIZE = $old_i/INITIAL_WINDOW_SIZE = $i/g" controller.hh
  make
  ./run-contest warmup &> output_b/window_${i}.out
  old_i=$i
done
