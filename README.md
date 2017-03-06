Tests for SCHED_DEADLINE
========================

This is a minimal set of scripts to test and visualize on kernelshark the
behavior of SCHED_DEADLINE under several corcumstances (e.g., migration, switch
to CFS, parameters change, etc.).

Requirements
------------

 - A Linux kernel 3.14+ compiled with the following symbols:
   - ```CONFIG_FTRACE```
   - ```CONFIG_FTRACE_SYSCALLS```
   - ```CONFIG_CPUSETS=y```
   - ```CONFIG_CGROUPS=y```
   - ```CONFIG_CGROUP_SCHED=y```
   - ```CONFIG_FAIR_GROUP_SCHED=y```
   - ```CONFIG_PROC_PID_CPUSET=y```
   - ```CONFIG_CGROUP_PIDS=y```
 - A Linux distribution with the following packages installed:
   - ```make```
   - ```gcc```
   - ```xinit```
   - ```trace-cmd```
   - ```kernelshark```
   - ```psmisc```

Usage
-----

 - Run

              ./run.sh

 - Then, check the results with

              ./check.sh

