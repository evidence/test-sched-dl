#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sched_utils.h"

int flag = 0;

pthread_mutex_t mutex;

void *periodic_change(__attribute__ ((unused)) void* param)
{

        for(;;){
		pthread_mutex_lock(&mutex);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
        return NULL;
}


int main (int argc, char *argv[])
{
	if (argc > 1)
		flag = atoi(argv[1]);
        pthread_t t;
	pthread_mutex_init(&mutex, NULL);
        pthread_create(&t, NULL, periodic_change, NULL);


        unsigned int flags = 0;
        struct sched_attr attr;
        attr.size = sizeof(attr);
        attr.sched_nice = 0;
        attr.sched_priority = 0;
	attr.sched_flags = flag;
        /* This creates a 10ms/30ms reservation */
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 30 * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = 40 * 1000 * 1000;
        if (sched_setattr(gettid(), &attr, flags) < 0){
		int fd = open ("dmesg.txt", O_WRONLY|O_CREAT);
		char* error_msg = "ERROR: sched_setattr()\n";
		write(fd, error_msg, strlen(error_msg));
		fsync(fd);
		close(fd);
                perror("sched_setattr()");
        }

        for(;;){
		pthread_mutex_lock(&mutex);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
        return 0;
}



