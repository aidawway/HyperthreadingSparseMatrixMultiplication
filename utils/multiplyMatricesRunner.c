#include <stdio.h>
#include <stdlib.h>
#include "multiplyMatrices.h"
#include "matrixUtils.h"

/**
 * This process is used in validating the accuracy
 * of matrix multiplication.
 *@arg1 - the name of the input file for the first SparseMatrix
 *@arg2 - the name of the input file for the second SparseMatrix
 *@arg3 - the name of the output file
 */
int main(int argc, char ** argv) {

	//parse data
	struct SparseMatrix * sm1 = parseSparseMatrix(*(argv + 1));
	struct SparseMatrix * sm2 = parseSparseMatrix(*(argv + 2));
	FILE* output = fopen(*(argv + 3), "w");

	//multiply matrices
	struct SparseMatrix * product = multiplySparseMatrices(sm1, sm2);

	//Write product
      fprintf(output, "%i, %i\n", product -> n, product -> nnz);
      for (int i = 0; i < product -> usage; i++) {
              fprintf(output, "%lf, ", *(product -> data + i));
      }
      fprintf(output, "\n");
      for (int i = 0; i < product -> usage; i++) {
              fprintf(output, "%i, ", *(product -> columnIndices + i));
      }
      fprintf(output, "\n");
      for (int i = 0; i < product -> n + 1; i++) {
              fprintf(output, "%i, ", *(product -> rowIndices + i));
      }
      fprintf(output, "\n");
	fflush(output);
	fclose(output);
}
