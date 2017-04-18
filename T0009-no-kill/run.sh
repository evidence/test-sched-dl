#!/bin/bash

make clean_data
DIR=`basename $PWD`
if [ ! -e $DIR ]; then
	echo "ERROR: File not compiled! Type make"
	exit
fi
$TRACECMD reset
rm -f dmesg.txt
$TRACECMD start -a -r 90 -b 100000 -e sched -e power
echo "Running test $DIR..."
dmesg -c > /dev/null
./$DIR $TESTDL_SCHED_FLAG
dmesg -c >> ./dmesg.txt
chmod 777 dmesg.txt
$TRACECMD extract -o trace.dat
$TRACECMD stop

