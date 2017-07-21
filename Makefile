
all: determinant-debug matrix-generator
clean: determinant matrix-generator
debug: determinant-debug matrix-generator
hack: determinant-hack matrix-generator

determinant-hack: main-hack.o determinants-hack.o
	gcc main-hack.o determinants-hack.o -o determinant -pthread -lm

determinant-debug: main-debug.o determinants-debug.o
	gcc main-debug.o determinants-debug.o -o determinant -pthread -lm

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
	
determinants-hack.o: determinants.c determinants.h
	gcc -c determinants.c -pthread -lm -o determinants-hack.o	-D DEBUG -D ZERO
	
main-hack.o: main.c determinants.h
	gcc -c main.c -pthread -lm -o main-hack.o -D DEBUG -D ZERO
	
matrix-generator: matrix-generator.c
	gcc -o matrix-generator matrix-generator.c -lm 