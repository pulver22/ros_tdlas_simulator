#include "utility.h"
#include "mtwist.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

// Returns the minimum of two values
int mini(int value1, int value2) {
	return (value1 < value2 ? value1 : value2);
}

// Returns the minimum of two values
double mind(double value1, double value2) {
	return (value1 < value2 ? value1 : value2);
}

// Returns the maximum of two values
int maxi(int value1, int value2) {
	return (value1 > value2 ? value1 : value2);
}

// Returns the maximum of two values
double maxd(double value1, double value2) {
	return (value1 > value2 ? value1 : value2);
}

// Returns the factorial.
int factorial(int x) {
	int fac = 1;
	int i = 0;
	for (i = 2; i <= x; i++) {
		fac *= i;
	}
	return fac;
}

// Returns P(X=x) if X~Poisson(lambda).
double poisson_pdf(double lambda, double x) {
	return pow(lambda, x) * exp(-lambda) / factorial(x);
}

// Returns a sample of X if X~Poisson(lambda) estimated with n trials.
int poisson_random(double lambda, int n) {
	int i;
	int count = 0;
	int threshold = (int)floor(lambda * (double)0x10000 / n);
	for (i = 0; i < n; i++) {
		if ((mt_lrand() & 0xffff) < threshold) {
			count++;
		}
	}
	return count;
}

struct timeval utility_timer_start;

// Start the timer.
void timer_start() {
	gettimeofday(&utility_timer_start, 0);
}

// Stops the timer and prints the elapsed time.
void timer_stop(const char *label) {
	struct timeval utility_timer_stop;
	struct timeval utility_timer_diff;
	gettimeofday(&utility_timer_stop, 0);
	utility_timer_diff.tv_sec = utility_timer_stop.tv_sec - utility_timer_start.tv_sec;
	utility_timer_diff.tv_usec = utility_timer_stop.tv_usec - utility_timer_start.tv_usec;
	if (utility_timer_diff.tv_usec < 0) {
		utility_timer_diff.tv_usec += 1000000;
		utility_timer_diff.tv_sec -= 1;
	}
	printf("%s: %ld.%06d\n", label, utility_timer_diff.tv_sec, utility_timer_diff.tv_usec);
}
