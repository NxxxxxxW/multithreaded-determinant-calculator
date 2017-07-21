#include <stdlib.h>
#include <stdio.h>
#include "determinants.h"

struct nMatrix* loadmatrix(char *filename);
int num_of_threads = 1;

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <matrix file> <num of threads>\n", argv[0]);
		exit(0);
	}
	
	struct nMatrix* m = loadmatrix(argv[1]);
	
	num_of_threads = atoi(argv[2]);
	
	#ifdef DEBUG	
		printmatrix(m);
	#endif
	
	printf("%ld\n", determinant_threaded_setup(m));
	
	freematrix(m);
}


struct nMatrix* loadmatrix(char *filename) {
	
	FILE *matrixfile = fopen(filename, "r");
	
	if (matrixfile == NULL) {
		perror("Couldn't open file\n");
		exit(-1);
	}
	
	int i, j, k, n;
	
	if (fscanf(matrixfile, " %d", &(n)) == 0) {
		fprintf(stderr, "Empty file :/\n");
		exit(-1);
	}
	
	struct nMatrix *m = newmatrix(n);
	m->n = n;
	
	#ifdef DEBUG
		fprintf(stdout, "Preparing to load a %dx%d matrix...\n", n, n);
	#endif
	
	for (i = 0; i < n; i++) {		
		for (j = 0; j < n; j++) {	
			if (fscanf(matrixfile, " %d", &(m->matrix[i][j])) == 0) {
				fprintf(stderr, "Not enough lines. Should be %dx%d", n, n);
				freematrix(m);
				exit(-1);
			}
		}
	}
	
	fclose(matrixfile);
	
	return m;
	
}
