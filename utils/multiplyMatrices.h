#ifndef MULTIPLY_MATRICES_H
#define MULTIPLY_MATRICES_H

#include "matrixUtils.h"

/**
 * This function multiplies to square SparseMatrices together and returns
 * the result.
 *@param sm1 - the left hand operand
 *@param sm2 - the right hand operand
 *@return - the product
 */
struct SparseMatrix * multiplySparseMatrices(struct SparseMatrix * sm1, struct SparseMatrix * sm2);

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
void sMAddNewLastPoint(struct SparseMatrix * sm, int i, int j, double p);


/**
 * This is a helper function used by multiplySparseMatrices.
 * This function updates all rowIndices for emptry rows
 *@param sm - the SparseMatrix to update
 */
void finalizeMatrix(struct SparseMatrix * sm);

#endif
