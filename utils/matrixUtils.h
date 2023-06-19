#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H
#include <stdio.h>
#include <stdlib.h>

//stores the necesary data 
//for a SparseMatrix
struct SparseMatrix {
	//the non zero data
	double * data;
	
	//the columnIndices of the corresponding
	//values in data
	int * columnIndices;

	//the index in data of the next nnz element
	//at this row or lower
	int * rowIndices;

	//the number of rows
	int n;

	//the number of nonzero elements in a finalized matrix,
	//otherwise the space allocated for nonzero elements
	int nnz;

	//the number of nonzero elements in an unfinalized matrix,
	//otherwise undefined
	int usage;
};

/**
 * Allocate space for a new SparseMatrix and fill it
 * with the data in file name
 * @param name - the name of the input file
 * @return - the SparseMatrix made from the data in the input file
 */
struct SparseMatrix* parseSparseMatrix(char* name);

/**
 * Fill the SparseMatrix sm with the data from name
 *@param name - the name of the input file
 *@param sm - points to the SparseMatrix* to fill
 */
void initiateSparseMatrix(char* name, struct SparseMatrix* sm);


/**
 * Allocate a SparseMarix
 *@param n - the dimension of the matrix
 *@param nnz - the number of nnz elements to allocate space for
 *@return - the allocated SparseMatrix
 */
struct SparseMatrix* sMalloc(int n, int nnz);

/**
 * Will get return the value of m at row r and column c
 *@param m - the SparseMatrix to search
 *@param r - the row of the data to get
 *@param c - the column of the data to get
 *return - the value at the given row and column in m
 */
double getCSRValue(struct SparseMatrix * m, int r, int c);
#endif
