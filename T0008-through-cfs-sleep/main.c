#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sched_utils.h"

int flag = 0;

void *periodic_change(void* param)
{
        int tid = *((int*) param);
        for (int i = 0;; ++i) {
                unsigned int flags = 0;
                struct sched_attr attr;
                attr.size = sizeof(attr);
                attr.sched_nice = 0;
		attr.sched_flags = flag;
                attr.sched_priority = 0;
                if (i%2){
                        /* This creates a 10ms/30ms reservation */
                        attr.sched_policy = SCHED_DEADLINE;
                        attr.sched_runtime = 10 * 1000 * 1000;
                        attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;
                } else {
                        attr.sched_policy = SCHED_OTHER;
                }
                if (sched_setattr(tid, &attr, flags) < 0)
                        perror("sched_setattr()");
                sleep(1);
        }
        return NULL;
}


int main (int argc, char *argv[])
{
	if (argc > 1)
		flag = atoi(argv[1]);
        pthread_t t;
        int tid = gettid();
        pthread_create(&t, NULL, periodic_change, (void *) &tid);

        sleep(100);
        return 0;
}



