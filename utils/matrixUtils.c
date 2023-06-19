#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrixUtils.h"

/**
 * Allocate space for a new SparseMatrix and fill it
 * with the data in file name
 * @param name - the name of the input file
 * @return - the SparseMatrix made from the data in the input file
 */
struct SparseMatrix* parseSparseMatrix(char* name) {
	//Initialize values
	FILE* input = fopen(name, "r");
	struct SparseMatrix * sm = calloc(1, sizeof(struct SparseMatrix));
	int n, nnz;
	
	//read the size of the matrix and the
	//number of nonzero values
	fscanf(input, "%i, %i", &n, &nnz);
	sm -> n = n;
	sm -> usage = nnz;
	sm -> nnz = nnz;
	
	//allocate space
	sm -> data = calloc(nnz, sizeof(double));
	sm -> columnIndices = calloc(nnz, sizeof(int));
	sm -> rowIndices = calloc(n + 1, sizeof(int));

	//read data
	for (int i = 0; i < nnz; i++) {
		fscanf(input, "%lf, ", sm -> data + i);
	}
	for (int i = 0; i < nnz; i++) {
		fscanf(input, "%i, ", sm -> columnIndices + i);
	}
	for (int i = 0; i < n + 1; i ++) {
		fscanf(input, "%i, ", sm -> rowIndices + i);
	}
	fclose(input);
	
	return sm;
}

/**
 * Fill the SparseMatrix sm with the data from name
 *@param name - the name of the input file
 *@param sm - points to the SparseMatrix* to fill
 */
void initiateSparseMatrix(char* name, struct SparseMatrix* sm) {
	//open input file
	FILE* input = fopen(name, "r");
        
	//read the dimensions of the matrix and the number
	//of nonzero elements
	int n, nnz;
        fscanf(input, "%i, %i", &n, &nnz);
        sm -> n = n;
        sm -> usage = nnz;
        sm -> nnz = nnz;

	//allocate space
        sm -> data = calloc(nnz, sizeof(double));
        sm -> columnIndices = calloc(nnz, sizeof(int));
        sm -> rowIndices = calloc(n + 1, sizeof(int));

	//scan data in
        for (int i = 0; i < nnz; i++) {
                fscanf(input, "%lf, ", sm -> data + i);
        }
        for (int i = 0; i < nnz; i++) {
                fscanf(input, "%i, ", sm -> columnIndices + i);
        }
        for (int i = 0; i < n + 1; i ++) {
                fscanf(input, "%i, ", sm -> rowIndices + i);
        }
        fclose(input);

}

/**
 * Allocate a SparseMarix
 *@param n - the dimension of the matrix
 *@param nnz - the number of nnz elements to allocate space for
 *@return - the allocated SparseMatrix
 */
struct SparseMatrix * sMalloc(int n, int nnz) {

	//allocate space 
	struct SparseMatrix * sm = malloc(sizeof(struct SparseMatrix));

	//set known values and allocate space
	sm -> n = n;
	sm -> nnz = nnz;
	sm -> usage = 0;
	sm -> data = malloc (nnz * sizeof(double));
	sm -> columnIndices = malloc(nnz * sizeof(int));
	sm -> rowIndices = malloc((n + 1) * sizeof(int));
	*(sm -> rowIndices + n) = n;

	//initialize unused data to -1
	for (int i = 0; i < nnz; i++) {
		*(sm -> data + i) = -1;
		*(sm -> columnIndices + i) = -1;
	} 
	for (int i = 0; i < n + 1; i++) {
		*(sm -> rowIndices + i) = -1;
	}

	return sm;
}

/**
 * Will get return the value of m at row r and column c
 *@param m - the SparseMatrix to search
 *@param r - the row of the data to get
 *@param c - the column of the data to get
 *return - the value at the given row and column in m
 */
double getCSRValue(struct SparseMatrix * m, int r,int c) {
	
	//get the range of nonzero columns in
	//the given row
	int r_start = *(m -> rowIndices + r);
	int r_end = *(m -> rowIndices + r + 1);
	
	//Search for the appropriate column, otherwise return 0
	//Note: the number of nonzero elements in a given row is
	//assumed to be small as this is a SparseMatrix. Therefore
	//a linear search should be sufficient.	
	for (int i = r_start; i < r_end; i++) {
		int c_curr = *(m -> columnIndices + i);
		if (c == c_curr) {
			return *(m -> data + i);
		}
		else if (c < c_curr) {
			return 0;
		}
	}
	return 0;
	
}

