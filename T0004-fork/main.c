#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sched_utils.h"

int flag = 0;

int main (int argc, char *argv[])
{
	if (argc > 1)
		flag = atoi(argv[1]);
	unsigned int flags = 0;
	struct sched_attr attr;
	attr.size = sizeof(attr);
	attr.sched_flags = flag;
	attr.sched_nice = 0;
        attr.sched_priority = 0;

	/* This creates a 10ms/30ms reservation */
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 10 * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

        if (sched_setattr(0, &attr, flags) < 0){
		int fd = open ("dmesg.txt", O_WRONLY);
		char* error_msg = "ERROR: sched_setattr()";
		write(fd, error_msg, strlen(error_msg));
		fsync(fd);
		close(fd);
                perror("sched_setattr()");
        }

        /* Fork must fail */
        int ret = fork();
        if (ret >= 0) {
		int fd = open ("dmesg.txt", O_WRONLY);
		char* error_msg = "ERROR: fork() not failed";
		write(fd, error_msg, strlen(error_msg));
		fsync(fd);
		close(fd);
                perror("sched_setattr()");
        }
	return 0;
}
