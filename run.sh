#!/bin/bash

rm result/$1.txt
for i in {1..20..1}
	do
		echo "running using $i thread(s)"
		export OMP_NUM_THREADS=$i
		icc -qopenmp -std=c++11 main.cpp
		./a.out $1 $2 $i >> result/$1.txt
done
