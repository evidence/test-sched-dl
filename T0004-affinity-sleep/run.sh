#!/bin/bash

make clean_data
DIR=`basename $PWD`
if [ ! -e $DIR ]; then
	echo "ERROR: File not compiled! Type make"
	exit
fi
trace-cmd reset
echo "Running test $DIR..."
dmesg -c > /dev/null
trace-cmd record -a -r 90 -b 100000 -e sched -o trace.dat ./$DIR $1 &
sleep 3
## ps aux | grep -i $DIR
PID=`ps aux | grep -i $DIR | grep -v trace-cmd | grep -v grep | xargs -r | awk '{print $2}'`
if [[ $PID == "" ]]; then
	echo "ERROR: no PID!"
	ps aux | grep -i $DIR
else
	echo "PID is $PID"
	echo $PID > /dev/cpuset/cpu0/tasks
	sleep 2
	echo $PID > /dev/cpuset/cpu1/tasks
	sleep 2
	echo $PID > /dev/cpuset/cpu0/tasks
	sleep 2
	echo $PID > /dev/cpuset/cpu1/tasks
	sleep 2
	echo $PID > /dev/cpuset/cpu0/tasks
	sleep 2
fi
echo "Killing test $DIR..."
killall $DIR > /dev/null
sleep 3
dmesg -c > ./dmesg.txt

