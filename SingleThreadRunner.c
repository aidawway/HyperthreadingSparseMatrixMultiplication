#define _GNU_SOURCE
#ifndef _XOPEN_SOURCE
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPENSOURCE 500
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include "assert.h"
#include "utils/multiplyMatrices.h"
#include "utils/matrixUtils.h"
#include "utils/TimeSpecUtils.h"

/**
 * The main Single threaded function that runs a
 * Single threaded test.
 *@arg1 - the name of the input file for the left hand operator list
 *@arg2 - the name of the input file for the right hand operator list
 *@arg3 - the number of multiplications to do
 *@arg4 - the size of each the matrix
 *@arg5 - the name of the output file
 */
int main(int argc, char ** argv) {
	if (argc < 5) {
		printf("m1_input_file, m2_input_file, n, size, output_file\n");
		exit(0);
	}

	//parse data
	FILE * m1_input_list = fopen(*(argv + 1), "r");
	FILE * m2_input_list = fopen(*(argv + 2), "r");
	int n = atoi(*(argv + 3));

	struct SparseMatrix * sm1_list = calloc(n, sizeof(struct SparseMatrix));
	struct SparseMatrix * sm2_list = calloc(n, sizeof(struct  SparseMatrix));
	

	for (int i = 0; i < n; i++) {
		char * name1 = calloc(100, sizeof(char));
		char * name2 = calloc(100, sizeof(char));
		fscanf(m1_input_list, "%s\n", name1);
		fscanf(m2_input_list, "%s\n", name2);
		initiateSparseMatrix(name1, sm1_list + i);
		initiateSparseMatrix(name2, sm2_list + i); 	
		free(name1);
		free(name2);
	}

	//restrict to one core 
	cpu_set_t set;	
        sched_getaffinity(0, sizeof(cpu_set_t), &set);
        CPU_ZERO(&set);
        CPU_SET(1, &set);
        assert(sched_setaffinity(0, sizeof(cpu_set_t), &set) == 0);

	//start timing
	struct timespec startTime;
	struct timespec endTime; 
	clock_gettime(CLOCK_REALTIME, &startTime);

	
	//compute matrix multiplications
	for (int i = 0; i < n; i++) {
		struct SparseMatrix * sm = multiplySparseMatrices(sm1_list + i, sm2_list + i);
		free(sm);
	}


	//end time
	clock_gettime(CLOCK_REALTIME, &endTime);
        struct timespec timeTaken;
        diffTimeSpec(&timeTaken, &endTime, &startTime);

	//print results
        printf("Time Taken: %ld.%.9ld\n", (long)timeTaken.tv_sec, (long int)timeTaken.tv_nsec);
	printf("done\n");

	int size = atoi(*(argv + 4));	
	FILE* output = fopen(*(argv + 5), "a");
	fprintf(output, "%i iterations of size %i took %ld.%.9ld seconds\n", n, size, (long)timeTaken.tv_sec, (long int)timeTaken.tv_nsec);
}
