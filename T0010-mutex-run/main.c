#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sched_utils.h"

int flag = 0;

pthread_mutex_t mutex;

void *periodic_change(void* param)
{
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
        if (sched_setattr(getpid(), &attr, flags) < 0)
                perror("sched_setattr()");

        for(;;){
		pthread_mutex_lock(&mutex);
		for (unsigned long int i = 0; i < 1000000; ++i);
		pthread_mutex_unlock(&mutex);
		for (unsigned long int i = 0; i < 1000000; ++i);
	}
        return NULL;
}


int main (int argc, char *argv[])
{
	if (argc > 1)
		flag = atoi(argv[1]);
        pthread_t tid;
	pthread_mutex_init(&mutex, NULL);
        int pid = getpid();
        pthread_create(&tid, NULL, periodic_change, (void *) &pid);

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
        if (sched_setattr(pid, &attr, flags) < 0)
                perror("sched_setattr()");

        for(;;){
		pthread_mutex_lock(&mutex);
		for (unsigned long int i = 0; i < 1000000; ++i);
		pthread_mutex_unlock(&mutex);
		for (unsigned long int i = 0; i < 1000000; ++i);
	}
        return 0;
}



