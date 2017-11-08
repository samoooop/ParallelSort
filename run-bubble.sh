#!/bin/bash

for i in {1..20..1}
	do
		echo "running using $i thread(s)"
		export OMP_NUM_THREADS=$i
		icc -qopenmp -std=c++11 Bubble.cpp
		./a.out 125000 >> Bubble.txt
done
