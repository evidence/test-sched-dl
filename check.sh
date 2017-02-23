#!/bin/bash


do_check() {
	echo "==================================="
	echo "==================================="
	echo "Checking directory $1"
	cd $1
	cat dmesg.txt
        echo "-----------------------------------"
        echo "-----------------------------------"
        sleep 1
	kernelshark ./trace.dat
	cd ..
}



if [[ $1 == "" ]];then
	for TEST in `ls -d T0* | xargs -r`; do
		do_check $TEST
	done
else
	do_check $1
fi
