#ifndef THREADS_SPECIFIED
	#define THREADS 1
#endif

struct nMatrix {
	// should use long
	int **matrix;
	int n;
	
};

long determinant_threaded_setup(struct nMatrix* m);
long determinant_nonthreaded(struct nMatrix *m);
struct nMatrix* submatrix_copy(struct nMatrix *m, int i, int j);
struct nMatrix* newmatrix(int n);

void freematrix(struct nMatrix *m);

void printmatrix(struct nMatrix* m);