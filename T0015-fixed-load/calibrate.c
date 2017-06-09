#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "sched_utils.h"


int main (int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s cycles\n", argv[0]);
		exit(-1);
	}

	long int cycles = atol(argv[1]);
	printf("Calibrating for %ld...\n", cycles);

	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	for (int i = 0; i < cycles; ++i);
	clock_gettime(CLOCK_REALTIME, &t2);

	long elapsed_usec =
		((t2.tv_sec - t1.tv_sec)*1000000) +
		((t2.tv_nsec - t1.tv_nsec)/1000);

	long elapsed_msec =
		((t2.tv_sec - t1.tv_sec)*1000) +
		((t2.tv_nsec - t1.tv_nsec)/1000000);

	printf("Elapsed: %ld usec\n", elapsed_usec);
	printf("Elapsed: %ld msec\n", elapsed_msec);
	printf("1 msec = %ld cycles\n", cycles/elapsed_msec);

	return 0;
}



