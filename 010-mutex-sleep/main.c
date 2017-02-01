#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sched_utils.h"

pthread_mutex_t mutex;

void *periodic_change(void* param)
{

        for(;;){
		pthread_mutex_lock(&mutex);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
        return NULL;
}


int main (void)
{
        pthread_t tid;
	pthread_mutex_init(&mutex, NULL);
        int pid = getpid();
        pthread_create(&tid, NULL, periodic_change, (void *) &pid);


        unsigned int flags = 0;
        struct sched_attr attr;
        attr.size = sizeof(attr);
        attr.sched_flags = 0;
        attr.sched_nice = 0;
        attr.sched_priority = 0;
        /* This creates a 10ms/30ms reservation */
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 30 * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = 40 * 1000 * 1000;
        if (sched_setattr(pid, &attr, flags) < 0)
                perror("sched_setattr()");

        for(;;){
		pthread_mutex_lock(&mutex);
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
        return 0;
}



