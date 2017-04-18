#!/bin/bash

make clean_data
DIR=`basename $PWD`
if [ ! -e $DIR ]; then
	echo "ERROR: File not compiled! Type make"
	exit
fi
$TRACECMD reset
rm -f dmesg.txt
echo "Running test $DIR..."
dmesg -c > /dev/null
$TRACECMD record -a -r 90 -b 100000 -e sched -e power -o trace.dat ./$DIR $TESTDL_SCHED_FLAG &
sleep 10
echo "Killing test $DIR..."
killall -s SIGKILL $DIR > /dev/null
sleep 3
dmesg -c >> ./dmesg.txt
chmod 777 dmesg.txt

