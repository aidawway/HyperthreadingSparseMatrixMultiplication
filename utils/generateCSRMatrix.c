#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generateCSRMatrix.h"

/**
 * This process makes writes a n by n SparseMatrix with
 * nnz number of nonzero values to the provided output file
 *@param 1 - output file
 *@param 2 - n
 *@param 3 - nnz
 */
int main(int argc, char** argv) {
	
	if (argc < 4) {
		printf("please input outputFile, n, nnz \n");
		exit(0);
	}
	
	//set seed
	srand(time(NULL));

	//parse input
	FILE* output = fopen(*(argv + 1), "w");	
	int n = atoi (*(argv + 2));
	int nnz = atoi(*(argv + 3));

	//allocate space
	double * data = calloc(nnz, sizeof(double));
	int * cI = calloc (nnz, sizeof(int));
	int * rI = calloc(n + 1, sizeof(int));
	*(rI + n) = nnz;
	
	//fill data with random values
	for (int i = 0; i < nnz; i++) {
		*(data + i) = (double) rand() / (double) RAND_MAX;
	}
	
	//rows are initially set to -1
	for (int i = 0; i < n; i++) {
		*(rI + i) = -1;
	}
	*(rI + n) = nnz;

	//place the values in random locations within the Sparse Matrix
	//Adapted from code found on stackoverflow by AndreyT on the
	//question: Unique random numbers in an integer array in the C programming language [duplicate]

	int max = ipow(n, 2);
	int found = 0;
	int currRow = -1;
	for (int ri = 0; ri < max; ri++) {
		double remaining = max - ri;
		double needed = nnz - found;
		int row = ri / n;
		if (rand() % (int)remaining < needed) {
			int column = ri % n;
			*(cI + found) = column;
			if (row > currRow) {
				currRow = row;
				*(rI + row) = found;
			} 
			found++;
		}
	}  
	//end adaptation
	
	//update rowIndices in any empty rows
	*rI = 0;	
	 for (int i = n; i > -1; i--) {
                if (*(rI + i) == -1) {
                        *(rI + i) = *(rI + i + 1);
                }
        }

	//print to file
	fprintf(output, "%i, %i\n", n, nnz);
	for (int i = 0; i < nnz; i++) {
		fprintf(output, "%lf, ", *(data + i));
	}
	fprintf(output, "\n");
	for (int i = 0; i < nnz; i++) {
		fprintf(output, "%i, ", *(cI + i));
	}
	fprintf(output, "\n");
	for (int i = 0; i < n + 1; i++) {
		fprintf(output, "%i, ", *(rI + i));
	}
	fprintf(output, "\n");
	printf("done\n");

	
}

//returns base to the exp power
int ipow(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
	
}


