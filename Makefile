
all: determinant determinant-debug matrix-generator
nodebug: determinant matrix-generator
debug: determinant-debug matrix-generator


determinant-debug: main-debug.o determinants-debug.o
	gcc main-debug.o determinants-debug.o -o determinant-debug -pthread -lm

determinant: main.o determinants.o
	gcc main.o determinants.o -o determinant -pthread -lm

main.o: main.c determinants.h
	gcc -c main.c -pthread -lm

determinants.o: determinants.c determinants.h
	gcc -c determinants.c -pthread -lm
	
determinants-debug.o: determinants.c determinants.h
	gcc -c determinants.c -pthread -lm -o determinants-debug.o	-D DEBUG
	
main-debug.o: main.c determinants.h
	gcc -c main.c -pthread -lm -o main-debug.o -D DEBUG
	
matrix-generator: matrix-generator.c
	gcc -lm -o matrix-generator matrix-generator.c