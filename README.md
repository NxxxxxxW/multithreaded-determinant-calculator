# Multithreaded-determinant-calculator
A toy which is for calculating determinants with threads

## Usage
### Matrix-generator
Generate NxN matrices with matrix-generator
```
	Matrix-generator n modifier [srand] > output
```
n => Dimensions of the matrix

modifier => Multiply the rand statement . Currently matrix values are calculated by `round((rand()%(1000*modifier))/1000)`

srand => If there is a particular seed, otherwise srand will uses current time

output => Output the file for the generated matrix


### Determinant
Using threads to calculate determinant of input matrix.
```
	determinant input.txt #threads
```
Use the debug versions for more verbose outputs

Compile with `make x`, 
```
	x => '' ie 'make' will make the verbose debug version
	x => 'clean' ie 'make clean' will compile to only output the final determinant
	x => 'hack' ie 'make hack' will compile to take a shortcut if the cofactor of a matrix is 0. 
		This option impacts the threading, making threads not necessarily do equal work, but it allows
		one to calculate larger matrices.
```

### Timer script
How long the thread takes to calculate the determinant of n=4, 8, and 12 matrices by using 1, 2, and 4 threads.
```
	time.sh
```
