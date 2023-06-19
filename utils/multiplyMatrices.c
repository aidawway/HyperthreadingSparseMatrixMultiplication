#include <stdio.h>
#include <stdlib.h>
#include "matrixUtils.h"
#include "multiplyMatrices.h"



/**
 * This function multiplies to square SparseMatrices together and returns
 * the result.
 *@param sm1 - the left hand operand
 *@param sm2 - the right hand operand
 *@return - the product 
 */
struct SparseMatrix * multiplySparseMatrices(struct SparseMatrix * sm1, struct SparseMatrix * sm2) {

	//allocate space for the product
	struct SparseMatrix * product = sMalloc(sm1 -> n, sm1 -> nnz);

	//For every row in the product calculate all of the values
	for (int pri = 0; pri < sm1 -> n; pri++) {
		//for every column in the current row of product
		//calculate all of the values
		for (int pci = 0; pci < sm2 -> n; pci++) {
			double sum = 0;
			int ci = *(sm1 -> rowIndices + pri);
			int ci_max = *(sm1 -> rowIndices + pri + 1);

			//for all of the nonzero elements in this row of
			//sm1, multiply them by their corresponding element
			//in sm2 and add the result to sum
			for (; ci < ci_max; ci++) {
				int column = *(sm1 -> columnIndices + ci);
				double sm1v = *(sm1 -> data + ci);
				double sm2v = getCSRValue(sm2, column, pci);
				sum += sm1v * sm2v;
			}
			//update product if this element is nonzero
			if (sum != 0) {
				sMAddNewLastPoint(product, pri, pci, sum);
			}
		}
	}

	//update the rowIndices of any rows that were empty
	finalizeMatrix(product);	

	
	return product;


}


/**
 * This is a helper function used by multiplySparseMatrices.
 * This function adds the value p to sm at index i and j. It 
 * is assumed that all elements after sm(i,j) are currently zero.
 * Earlier empty rows are not updated yet.
 *@param sm - the SparseMatrix to update
 *@param i - the row to insert a value
 *@param j - the column to insert a value
 *@param p - the double to insert
 */
void sMAddNewLastPoint(struct SparseMatrix * sm, int i, int j, double p) {
        //Increase the allocated space for nonzero elements if needed
	if (sm -> usage == sm -> nnz) {
                sm -> data = realloc(sm -> data, sm -> nnz * 2 * sizeof(double));
                sm -> columnIndices = realloc(sm -> columnIndices, sm -> nnz * 2 * sizeof(int));
                for (int foo = sm -> nnz; foo < sm -> nnz * 2; foo++) {
                        *(sm -> data + foo) = -1;
                        *(sm -> columnIndices + foo) = -1;
                }
                sm -> nnz *= 2;
        }

	//add p to sm
        *(sm -> data + sm -> usage) = p;
        *(sm -> columnIndices + sm -> usage) = j;

	//if p is the first value in the row then
 	//update it's rowIndex
        if (*(sm -> rowIndices + i) == -1){
                *(sm -> rowIndices + i) = sm -> usage;
        }

	//update the usage
        sm -> usage++;
        *(sm -> rowIndices + sm -> n) = sm -> usage;

}

/**
 * This is a helper function used by multiplySparseMatrices.
 * This function updates all rowIndices for emptry rows
 *@param sm - the SparseMatrix to update
 */
void finalizeMatrix(struct SparseMatrix * sm) {

	//free any excess allocation
	sm -> data = realloc (sm -> data, sm -> usage * sizeof(double));
	sm -> columnIndices = realloc (sm -> columnIndices, sm -> usage * sizeof(int));
	sm -> nnz = sm -> usage;

	//Update rowIndices of empty rows
	for (int i = sm -> n - 1; i > -1; i--) {
		if (*(sm -> rowIndices + i) == -1) {
			*(sm -> rowIndices + i) = *(sm -> rowIndices + i + 1);
		}
	}
}

