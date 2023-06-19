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
#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include "assert.h"
#include "utils/multiplyMatrices.h"
#include "utils/matrixUtils.h"
#include "utils/TimeSpecUtils.h"

//This struct holds the arguments for the thread
struct thread_arg {
	//The list of left hand operands
	struct SparseMatrix * sm1_list;
	
	//The list of right hand operand
	struct SparseMatrix * sm2_list;

	//the number of multiplications to do
	int n;

	//Output for the timeTaken
	struct timespec * timeTaken;

	//The barrier to begin multiplying
	pthread_barrier_t * start_barrier;
};


/**
 * This function starts of a thread. 
 *@param arg - the arguments needed for the thread
 */
void thread_start(struct thread_arg * arg);

/**
 * The main Hyperthreading function that runs a 
 * Hyperthreading test. 
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
	
	//Parse info
	FILE * m1_input_list = fopen(*(argv + 1), "r");
	FILE * m2_input_list = fopen(*(argv + 2), "r");
	int N = atoi(*(argv + 3));
	int n = N/2;

	struct SparseMatrix * sm1_list = calloc(N, sizeof(struct SparseMatrix));
	struct SparseMatrix * sm2_list = calloc(N, sizeof(struct  SparseMatrix));
	
	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, 2);

	for (int i = 0; i < N; i++) {
		//printf("%i\n", i);
		char * name1 = calloc(100, sizeof(char));
		char * name2 = calloc(100, sizeof(char));
		fscanf(m1_input_list, "%s\n", name1);
		fscanf(m2_input_list, "%s\n", name2);
		initiateSparseMatrix(name1, sm1_list + i);
		initiateSparseMatrix(name2, sm2_list + i); 	
		free(name1);
		free(name2);
	}
	
	//Add the first half of the multiplications
	//to the child_arg for the spawned thread
	struct thread_arg child_arg;
	child_arg.sm1_list = sm1_list;
	child_arg.sm2_list = sm2_list;
	child_arg.n = n;
	child_arg.timeTaken = calloc(1, sizeof(struct timespec));
	child_arg.start_barrier = &barrier;

	//start child thread
	pthread_t thread_id;
	assert(pthread_create(&thread_id, NULL, thread_start, (void*)&child_arg) == 0);
	
	//Add the second half of the multiplications for 
	//the current thread
	struct thread_arg parent_arg;
	parent_arg.sm1_list = sm1_list + n;
	parent_arg.sm2_list = sm2_list + n;
	parent_arg.n = N - n;
	parent_arg.timeTaken = calloc(1, sizeof(struct timespec));
	parent_arg.start_barrier = &barrier;

	//execute the first half of the instructions
	thread_start(&parent_arg);

	//wait for child to finish
	pthread_join(thread_id, NULL);	
	
	//choose the longer TimeTaken
	struct timespec timeTaken;
	if (timeSpecIsGreaterThan(parent_arg.timeTaken, child_arg.timeTaken)) {
		timeTaken = *(parent_arg.timeTaken);
	} 
	else {
		timeTaken = *(child_arg.timeTaken);
	}

	//print results
	printf("Time Taken: %ld.%.9ld\n", (long)timeTaken.tv_sec, (long int)timeTaken.tv_nsec);
        printf("done\n");

	int size = atoi(*(argv + 4));
        FILE* output = fopen(*(argv + 5), "a");
        fprintf(output, "%i iterations of size %i took %ld.%.9ld seconds\n", N, size, (long)timeTaken.tv_sec, (long int)timeTaken.tv_nsec);
        fclose(output);

}


/**
 * This function starts of a thread.
 *@param arg - the arguments needed for the thread
 */
void thread_start(struct thread_arg * arg) {
	struct SparseMatrix * sm1_list = arg -> sm1_list;
	struct SparseMatrix * sm2_list = arg -> sm2_list;
	struct timespec * timeTaken = arg -> timeTaken;
	int n = arg -> n;
	
	//restrict the threads to the same core to force
	//hyperthreading
	cpu_set_t set;
        sched_getaffinity(0, sizeof(cpu_set_t), &set);
        CPU_ZERO(&set);
        CPU_SET(1, &set);
        assert(sched_setaffinity(0, sizeof(cpu_set_t), &set) == 0);

	//Ensure that the threads enter the timed section at the same time
	//to most accurately simulate a workload
	pthread_barrier_wait(arg -> start_barrier);

	//start timing this thread
	struct timespec startTime;
        struct timespec endTime;
        clock_gettime(CLOCK_REALTIME, &startTime);
	
	//compute the multiplications
	for (int i = 0; i < n; i++) {
		struct SparseMatrix * sm = multiplySparseMatrices(sm1_list + i, sm2_list + i);
		free(sm);
	}

	//end the timing for this thread
	clock_gettime(CLOCK_REALTIME, &endTime);
        diffTimeSpec(timeTaken, &endTime, &startTime);
}
