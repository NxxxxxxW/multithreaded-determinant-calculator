#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <size of NxN matrix> <matrix range modifier> [srand value]\n", argv[0]);
		exit(0);
	}
	
	int n = atoi(argv[1]);
	int i, j;
	double avg = atof(argv[2]);
	
	if (argc == 4) {
		srand(atoi(argv[3]));
	}
	else {
		srand(time(NULL));
	}
	
	
	fprintf(stdout, "%d\n", n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			double float_num = rand()%(int)(1000*avg);
			float_num /= 1000;
			float_num = round(float_num);
			fprintf(stdout, "%d ", (int)float_num);
		}
		fprintf(stdout, "\n");
	}
	

}