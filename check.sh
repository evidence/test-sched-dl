#!/bin/bash

for TEST in `ls -d T0* | xargs -r`; do
	echo "==================================="
	echo "==================================="
	echo "Checking directory $TEST"
	cd $TEST
	cat dmesg.txt
        echo "-----------------------------------"
        echo "-----------------------------------"
        sleep 1
	kernelshark ./trace.dat
	cd ..
done
