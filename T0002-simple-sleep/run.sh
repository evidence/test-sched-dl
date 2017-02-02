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
trace-cmd record -a -r 90 -b 100000 -e sched -o trace.dat ./$DIR &
sleep 10
echo "Killing test $DIR..."
killall $DIR > /dev/null
sleep 3
dmesg -c > ./dmesg.txt
cat dmesg.txt

