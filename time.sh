#!/bin/bash

for n in 4 8 12
do
	echo "$n x $n with seed 31"
	./matrix-generator $n 1 31 > $n.txt
	for t in 1 2 4
	do
		echo "$n x $n with $t threads:"
		time ./determinant-debug $n.txt $t
		echo " "
		echo " "
	done
	rm $n.txt
done