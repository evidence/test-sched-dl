#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include "sched_utils.h"

#define EXEC_MS		3
#define PERIOD_MS	10
#define NB_THREADS	8
#define CYCLES_PER_MS	123915

int flag = 0;

void *thread_body(__attribute__ ((unused)) void* param)
{
	struct timespec t1, t2;
        unsigned int flags = 0;
        struct sched_attr attr;
        attr.size = sizeof(attr);
        attr.sched_nice = 0;
        attr.sched_priority = 0;
	attr.sched_flags = flag;
        /* This creates a 3ms/10ms reservation */
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = EXEC_MS * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = PERIOD_MS * 1000 * 1000;
        if (sched_setattr(gettid(), &attr, flags) < 0) {
                perror("sched_setattr()");
		int fd = open ("dmesg.txt", O_WRONLY|O_CREAT);
		char* error_msg = "ERROR: sched_setattr()\n";
		write(fd, error_msg, strlen(error_msg));
		fsync(fd);
		close(fd);
		exit(-1);
	}

	while(1) {
		/* Execution */
		long int runtime = CYCLES_PER_MS * EXEC_MS;
		clock_gettime(CLOCK_REALTIME, &t1);
		for (int i = 0; i < runtime; ++i);
		clock_gettime(CLOCK_REALTIME, &t2);

		/* Sleep to next period */
		long elapsed_usec =
			((t2.tv_sec - t1.tv_sec)*1000000) +
			((t2.tv_nsec - t1.tv_nsec)/1000);
		long int slp = PERIOD_MS*1000 - elapsed_usec;
		usleep(slp);
	}
        return NULL;
}


int main (int argc, char *argv[])
{
	if (argc > 1)
		flag = atoi(argv[1]);
	pthread_t t [NB_THREADS];
	for (int i = 0; i < NB_THREADS; ++i)
        	pthread_create(&t[i], NULL, thread_body, NULL);

        for(;;);
        return 0;
}



