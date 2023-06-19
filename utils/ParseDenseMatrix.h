#ifndef PARSE_DENSE_MATRIX_H
#define PARSE_DENSE_MATRIX_H
#include "matrixUtils.h"


//used to store the coordinates of an element
struct coordinates {
	//the row index
	int r;

	//the column index
	int c;
};


/*
 * Helper functioncalled after incrementing the r value of a coordinate
 *@param coord - the coordinate to update
 *@param m - the SparseMatrix to find the next nonzero in
 *@param nzc - the index of the next nonzero to find in m -> data
 */
void postIncrementNextNZRow(struct coordinates * coord, struct SparseMatrix * m, int nzc);

#endif
