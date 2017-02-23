#!/bin/bash

# Uncomment to enable reclaiming:
FLAG=2

## Check if we have root permissions
if [ "`id -u`" != "0" ]; then
        echo "ERROR: Need to be root to run this script! Use 'sudo' command."
        exit
fi

do_clean() {
	echo "Killing all remaining tasks..."
	killall -r 'T00*'
	echo "Umounting /dev/cpuset..."
	umount /dev/cpuset
	echo "Resetting RT throttling..."
	echo 1000000 > /proc/sys/kernel/sched_rt_period_us
	echo  950000 > /proc/sys/kernel/sched_rt_runtime_us
}

do_test() {
	echo "==================================="
	echo "Entering directory $1"
	cd $1
	sudo ./run.sh $FLAG
	sleep 10
	cd ..
}

do_clean

if [[ "$FLAG" == "" ]]; then
	echo "Disabling RT throttling..."
	echo -1 > /proc/sys/kernel/sched_rt_period_us
	echo -1 > /proc/sys/kernel/sched_rt_runtime_us
	else
	echo "Setting RT throttling..."
	echo 1000000 > /proc/sys/kernel/sched_rt_period_us
	echo  950000 > /proc/sys/kernel/sched_rt_runtime_us
fi

if [ ! -e /dev/cpuset ]; then
	mkdir /dev/cpuset
fi
mount -t cgroup -o cpuset cpuset /dev/cpuset
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


if [[ $1 == "" ]];then
	echo "No test provided. Running all with flag $FLAG"
	for TEST in `ls -d T0* | xargs -r`; do
		do_test $TEST
	done
else
	echo "Running test $1 with flag $FLAG"
	do_test $1
fi

do_clean
echo "Test finished"
