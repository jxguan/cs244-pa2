#! /bin/bash
j=0
for i in 0 1 2 5 10 20 50 100 200 500
do
  sed -i "s/the_window_size = $j/the_window_size = $i/g" controller.cc
  make
  for n in 1 2 3
  do
    ./run-contest warmup &> output_a/window_${i}_${n}.out
  done
  j=$i
done
