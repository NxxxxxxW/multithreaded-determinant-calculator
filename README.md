# multithreaded-determinant-calculator
A toy for calculating determinants with threads

#Usage
##matrix-generator
Generate NxN matrices with matrix-generator
```
	matrix-generator n modifier [srand] > output
```
n => dimensions of the matrix

modifier => multiply the rand statement by this. Currently matrix values are calculated by `round((rand()%(1000*modifier))/1000)`

srand => if there is a particular seed, otherwise it will just use current time

output => output file for the generated matrix


##determinant
Calculates determinant of input matrix using threads
```
	determinant input.txt #threads
```
Use the debug versions for more verbose output

Compile with `make` 