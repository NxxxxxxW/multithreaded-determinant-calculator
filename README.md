# multithreaded-determinant-calculator
A toy for calculating determinants with threads

##Usage
###matrix-generator
Generate NxN matrices with matrix-generator
```
	matrix-generator n modifier [srand] > output
```
n => dimensions of the matrix

modifier => multiply the rand statement by this. Currently matrix values are calculated by `round((rand()%(1000*modifier))/1000)`

srand => if there is a particular seed, otherwise it will just use current time

output => output file for the generated matrix


###determinant
Calculates determinant of input matrix using threads
```
	determinant input.txt #threads
```
Use the debug versions for more verbose output

Compile with `make x`, 
```
	x => '' ie 'make' will make the verbose debug version
	x => 'clean' ie 'make clean' will compile to only output the final determinant
	x => 'hack' ie 'make hack' will compile to take a shortcut if the cofactor of a matrix is 0. 
		This option impacts the threading, making threads not necessarily do equal work, but it allows
		one to calculate larger matrices.
```

###timer script
Times how long it takes to calculate the determinant of n=4, 8, and 12 matrices using 1, 2, and 4 threads
```
	time.sh
```