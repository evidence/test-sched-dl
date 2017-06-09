#!/bin/sh

## Check if we have root permissions
if [ "`id -u`" != "0" ]; then
        echo "ERROR: Need to be root to run this script! Use 'sudo' command."
        exit
fi

CURRENT=`cat /sys/devices/system/cpu/cpufreq/policy0/scaling_governor`
echo "Current governor: $CURRENT"
echo performance > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor
TEST=`cat /sys/devices/system/cpu/cpufreq/policy0/scaling_governor`
echo "Test governor: $TEST"
chrt -f 99 ./calibrate 100000000
echo $CURRENT > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor
CURRENT=`cat /sys/devices/system/cpu/cpufreq/policy0/scaling_governor`
echo "Restored governor: $CURRENT"
