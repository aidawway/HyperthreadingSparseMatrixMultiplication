#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrixUtils.h"
#include "ParseDenseMatrix.h"

/**
 * This process is used in the validation of the
 * accuracy of multiplySparseMatrices.
 * This matrix converts a SparseMatrix into a DenseMatrix
 *@arg1 - the name of the input file for the SparseMatrix
 */
int main(int argc, char** argv) {
	
	//parse data
	struct SparseMatrix * sm = parseSparseMatrix(*(argv + 1));
	

	//the coordinates of the next nonzero element
	struct coordinates nextNZ = {0, 0};
	
	//nonzeroCount
	int nzc = 0;
	//find the first nonzero
	postIncrementNextNZRow(&nextNZ, sm, nzc);
	nextNZ.c = *(sm -> columnIndices + nzc);

	//print the dimension of the dense matrix
	printf("%i\n", sm -> n);

	//for every row of the dense matrix
	for (int i = 0; i < sm -> n; i++) {
		//for every column of the dense matrix
		for (int j = 0; j < sm -> n; j++) {
			//if before the next non zero or after the last nonzero
			//print zero. Otherwise print the value
			if (i < nextNZ.r || j < nextNZ.c || nzc == sm -> nnz) {
				printf("0.00000000, ");
			}
			else {
				//print the value
				printf("%lf, ", *(sm -> data + nzc++));
				
				//update the nextNZ columnIndice
				nextNZ.c= *(sm -> columnIndices + nzc);
			
				//update the nextNZ row index if neccesary
				if (nzc == *(sm -> rowIndices + nextNZ.r + 1)) { 
					nextNZ.r++;
					postIncrementNextNZRow(&nextNZ, sm, nzc);
				}
			}
		}
		printf("\n");
	}
}

/*
 * Helper functioncalled after incrementing the r value of a coordinate
 *@param coord - the coordinate to update
 *@param m - the SparseMatrix to find the next nonzero in
 *@param nzc - the index of the next nonzero to find in m -> data
 */
void postIncrementNextNZRow(struct coordinates * coord, struct SparseMatrix * m, int nzc) {
	//if there is no next nonzero then return
 	if (nzc == m -> nnz) {
		return;
	}

	//find the row with the next nonzero and update coord
	int * ri = m -> rowIndices;
	while ( *(ri + coord -> r) == *(ri + coord -> r + 1)) {
		 coord -> r++;
	}
}
