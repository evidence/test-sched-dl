#!/bin/bash

## Check if we have root permissions
if [ "`id -u`" != "0" ]; then
        echo "ERROR: Need to be root to run this script! Use 'sudo' command."
        exit
fi

echo "Disabling RT throttling..."
echo -1 > /proc/sys/kernel/sched_rt_period_us
echo -1 > /proc/sys/kernel/sched_rt_runtime_us


if [ ! -e /dev/cpuset ]; then
	mkdir /dev/cpuset
	mount -t cgroup -o cpuset cpuset /dev/cpuset
fi
echo 0 > /dev/cpuset/cpuset.sched_load_balance
echo 1 > /dev/cpuset/cpuset.cpu_exclusive
## echo 2 > /dev/cpuset/cpuset.cpus

if [ ! -e /dev/cpuset/cpu0 ]; then
	mkdir /dev/cpuset/cpu0
fi
echo 0 > /dev/cpuset/cpu0/cpuset.cpus
echo 0 > /dev/cpuset/cpu0/cpuset.mems
echo 1 > /dev/cpuset/cpu0/cpuset.cpu_exclusive
echo 0 > /dev/cpuset/cpu0/cpuset.mem_exclusive

if [ ! -e /dev/cpuset/cpu1 ]; then
	mkdir /dev/cpuset/cpu1
fi
echo 1 > /dev/cpuset/cpu1/cpuset.cpus
echo 0 > /dev/cpuset/cpu1/cpuset.mems
echo 1 > /dev/cpuset/cpu1/cpuset.cpu_exclusive
echo 0 > /dev/cpuset/cpu1/cpuset.mem_exclusive

for TEST in `ls -d 0* | xargs -r`; do
	echo "==================================="
	echo "Entering directory $TEST"
	cd $TEST
	sudo ./run.sh
	sleep 3
	cd ..
done
