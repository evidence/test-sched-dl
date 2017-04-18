#!/bin/bash

# Change to specify a specific path for kernelshark:
KERNELSHARK=kernelshark

do_check() {
	echo "Checking directory $1"
	cd $1
	if [[ `cat dmesg.txt | xargs -r` != "" ]]; then
		xterm -fa 'Monospace' -fs 12 -title $1 -e /bin/bash -c 'printf "Dmesg content:\n\n"; cat dmesg.txt; printf "\nPress Enter to close"; read;' &
	fi
	$KERNELSHARK ./trace.dat 2> /dev/null
	cd ..
}



if [[ $1 == "" ]];then
	for TEST in `ls -d T0* | xargs -r`; do
		do_check $TEST
	done
else
	do_check $1
fi
