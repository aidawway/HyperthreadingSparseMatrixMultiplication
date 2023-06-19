#
# A simple Makefile to build 'esh'
#

CFLAGS= -std=c99 -O3

all : multiplyMatricesRunner generateCSRMatrix parseDenseMatrix


 multiplyMatricesRunner : 
	gcc-12 $(CFLAGS) -O3 -o multiplyMatricesRunner multiplyMatricesRunner.c\
		multiplyMatrices.c multiplyMatrices.h matrixUtils.c matrixUtils.h

 generateCSRMatrix :
	gcc-12 $(CFLAGS) -o generateCSRMatrix generateCSRMatrix.c generateCSRMatrix.h

 parseDenseMatrix :
	gcc-12 $(CFLAGS) -o parseDenseMatrix ParseDenseMatrix.c ParseDenseMatrix.h\
		matrixUtils.c matrixUtils.h

clean : 
	rm multiplyMatricesRunner
	rm generateCSRMatrix
	rm parseDenseMatrix
