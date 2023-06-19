#ifndef TIME_SPEC_UTILS_H
#define TIME_SPEC_UTILS_H

#ifndef _XOPEN_SOURCE
#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif
#endif

#include <time.h>
#include <stdbool.h>

/**
 * This function adds two timespecs and placed the sum into output
 *@param output - the timespec to record the sum in
 *@param t1 - one timespec to add
 *@param t2 - the other timespec to add
 */
void addTimeSpec(struct timespec* output, struct timespec* t1, struct timespec* t2);

/**
 * This function subtracts two timespecs and placed the difference into output
 *@param output - the timespec to record the difference in
 *@param t1 - the left hand operand
 *@param t2 - the right hand operand
 */
void diffTimeSpec(struct timespec* output, struct timespec* t1, struct timespec* t2);

/**
 * This function returns true if t1 is greater than t2.
 * Otherwise it returns false.
 */
bool timeSpecIsGreaterThan(struct timespec * t1, struct timespec * t2);

#endif
