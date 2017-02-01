#!/bin/bash

## Check if we have root permissions

for TEST in `ls -d 0* | xargs -r`; do
	echo "==================================="
	echo "Checking directory $TEST"
	cd $TEST
	cat dmesg.txt
	kernelshark ./trace.dat
	cd ..
done
