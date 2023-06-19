#ifndef _XOPEN_SOURCE
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif
#endif

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define BILLION_NANO_SECONDS 1000000000

/**
 * This function adds two timespecs and placed the sum into output
 *@param output - the timespec to record the sum in
 *@param t1 - one timespec to add
 *@param t2 - the other timespec to add
 */
void addTimeSpec(struct timespec* output, struct timespec* t1, struct timespec* t2) {
	//add the values
	output -> tv_sec = t1 -> tv_sec + t2 -> tv_sec;
	output -> tv_nsec = t1 -> tv_nsec + t2 -> tv_nsec;
	
	//handle carry over
	if (output -> tv_nsec > BILLION_NANO_SECONDS) {
		output -> tv_sec++;
		output -> tv_nsec -= BILLION_NANO_SECONDS;
	}
}


/**
 * This function subtracts two timespecs and placed the difference into output
 *@param output - the timespec to record the difference in
 *@param t1 - the left hand operand
 *@param t2 - the right hand operand
 */
void diffTimeSpec(struct timespec* output, struct timespec* t1, struct timespec* t2) {
	//subtract the two timespecs
	output -> tv_sec = t1 -> tv_sec - t2 -> tv_sec;
        output -> tv_nsec = t1 -> tv_nsec - t2 -> tv_nsec;

	//handle underflow
        if (output -> tv_nsec < 0) {
                output -> tv_sec--;
                output -> tv_nsec += BILLION_NANO_SECONDS;
        }
}

/**
 * This function returns true if t1 is greater than t2.
 * Otherwise it returns false.
 */
bool timeSpecIsGreaterThan(struct timespec * t1, struct timespec * t2)  {
	if (t1 -> tv_sec > t2 -> tv_sec) {
		return true;
	}
	else if (t1 -> tv_sec == t2 -> tv_sec && t1 -> tv_nsec > t2 -> tv_nsec) {
		return true;
	}
	return false;
}
