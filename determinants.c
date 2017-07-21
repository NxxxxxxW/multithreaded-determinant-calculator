#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "determinants.h"

extern int num_of_threads;

struct matrixthread {
	struct nMatrix *matrix;
	int start;
	int end;	
};

long getcofactor(int i, int j, int a, struct nMatrix *m);
void *determinant_threaded(void *arg);


long determinant_threaded_setup(struct nMatrix* m) {
	int i;
	int start, end = m->n;
	int partition = (int)floor(m->n/(double)num_of_threads);
	pthread_t *pth = malloc(num_of_threads * sizeof(pthread_t));
	long joined_determinant = 0;
	
	#ifdef DEBUG
	fprintf(stderr, "parition size: %d\n", partition);
	#endif
	
	for (i = num_of_threads-1; i >= 0; i--) {
		start = i*partition;
		
		struct matrixthread *t = (struct matrixthread*)malloc(sizeof(struct matrixthread));
		t->matrix = m;
		t->start = start;
		t->end = end;
		
		#ifdef DEBUG
		fprintf(stderr, "thread #%d calculating from %d -> %d\n", i, start, end);
		#endif
		pthread_create(&pth[i], NULL, determinant_threaded, (void*)t);
		
		end = start;
		
	}
	
	
	
	for (i = 0; i < num_of_threads; i++) {
		void *returnValue;
		pthread_join(pth[i], &returnValue);
		//do something with det
		#ifdef DEBUG
		fprintf(stderr, "Thread %d returned determinant %ld\n", i, *(long*)returnValue);
		#endif
		joined_determinant += *(long*)returnValue;
	}
	return joined_determinant;
}

void *determinant_threaded(void *arg) {
	struct matrixthread *t = (struct matrixthread*)arg;
	long *det = malloc(sizeof(long));
	int i;
	
	for (i = t->start; i < t->end; i++) {
		long temp = getcofactor(i, 0, t->matrix->matrix[i][0], t->matrix);
		*det += temp;
		#ifdef DEBUG
		fprintf(stderr, "Sub determinant[%d][0] (%d) = %ld\n", i, t->matrix->matrix[i][0], temp);
		#endif
	}
	free(t);
	pthread_exit((void*)det);
	
	
}

long determinant_nonthreaded(struct nMatrix *m) {

	int i;
	int d = 0;
	int c = -1;
	
	if (m->n == 2) {
		return m->matrix[0][0]*m->matrix[1][1] -m->matrix[0][1]*m->matrix[1][0];
	}
	
	for (i = 0; i < m->n; i++) {
		d += getcofactor(i, 0, m->matrix[i][0], m);
	}
	
	return d;
} 

long getcofactor(int i, int j, int a, struct nMatrix *m) {
	
	struct nMatrix *u = submatrix_copy(m, i, 0);
	
	int c;
	
	if ((i+j)%2 == 0) c = 1;
	else			  c = -1;
	
	long det = c * a * determinant_nonthreaded(u);

	
	freematrix(u);
	return det;	
	
}

struct nMatrix* newmatrix(int n) {
	int i;
	
	struct nMatrix* m = (struct nMatrix*)malloc(sizeof(struct nMatrix));
	m->matrix = (int**)malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		m->matrix[i] = (int*)malloc(n * sizeof(int));
	}
	m->n = n;
	
	return m;
}


void freematrix(struct nMatrix* m) {
	
	int i;

	for (i = 0; i < m->n; i++) {
		free(m->matrix[i]);
	}
	
	free(m->matrix);
	free(m);
}

// i and j are the columns to delete
struct nMatrix* submatrix_copy(struct nMatrix *m, int i, int j) {
	struct nMatrix *u = newmatrix(m->n-1);
	int a, b, x, y;
	
	for (a = 0, x = 0; a < u->n; a++, x++) {
		for (b = 0, y = 0; b < u->n; b++, y++) {
			// loops through the indices of the u-array
			if (x == i) x++;
			if (y == j) y++;
			u->matrix[a][b] = m->matrix[x][y];
		}
	}
	
	return u;
}


void printmatrix(struct nMatrix* m) {
	int i, j;
	
	for (i = 0; i < m->n; i++) {
		for (j = 0; j < m->n; j++) {
			printf("%4d ", m->matrix[i][j]);
		}
		printf("\n");
	}
}