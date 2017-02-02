#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "sched_utils.h"

int main (void)
{
	unsigned int flags = 0;
	struct sched_attr attr;
	attr.size = sizeof(attr);
        attr.sched_flags = 0;
        attr.sched_nice = 0;
        attr.sched_priority = 0;

       /* This creates a 10ms/30ms reservation */
        attr.sched_policy = SCHED_DEADLINE;
        attr.sched_runtime = 10 * 1000 * 1000;
        attr.sched_period = attr.sched_deadline = 30 * 1000 * 1000;

        if (sched_setattr(0, &attr, flags) < 0)
                perror("sched_setattr()");
	else
		for (unsigned long int i = 0; i < 100000000; ++i);
	return 0;
}
