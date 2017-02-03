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
SEQ=$(seq 1 90)
for RUN in $SEQ
do
./$DIR $1 &
done
sleep 20
echo "Killing test $DIR..."
killall $DIR > /dev/null
sleep 3
dmesg -c > ./dmesg.txt

