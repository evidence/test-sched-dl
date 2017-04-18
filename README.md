Tests for SCHED_DEADLINE
========================

This is a minimal set of scripts to test and visualize on
[kernelshark](http://rostedt.homelinux.com/kernelshark/) the
behavior of the [SCHED_DEADLINE](https://en.wikipedia.org/wiki/SCHED_DEADLINE)
Linux scheduler under several circumstances (e.g., migration, switch to CFS,
parameters change, etc.).

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
   - ```xterm```

Usage
-----

 - Clean old results:

              make clean

 - Build:

              make

 - Run

              sudo ./run.sh [test]

   Note: for testing the [GRUB](http://lkml.iu.edu/hypermail/linux/kernel/1703.2/06174.html)
   algorithm, uncomment ```TESTDL_SCHED_FLAG=2``` inside ```run.sh```.

   Note: besides visualizing the kernelshark trace, you may want to instrument
   the code in ```deadline.c``` with ```printk``` instructions to check the
   correctness of specific portions of code.

 - Then, check the results with

              ./check.sh [test]


trace-cmd installation
----------------------

The `trace-cmd` and `kernelshark` tools are available by default in the
repositories of most Linux distributions.
If you rather prefer to download and build these tools from sources:

 - Install the needed build packages:

             sudo apt-get install build-essential gnome-devel

 - Get the source code of trace-cmd:

             git clone git://git.kernel.org/pub/scm/linux/kernel/git/rostedt/trace-cmd.git

             git checkout trace-cmd-v2.6

 - Build the tools:

             cd test-dl

             make

             make gui

 - Change inside `run.sh` and in `check.sh` the variables `TRACECMD` and
   `KERNELSHARK`, respectively.


Code coverage
-------------

 - Build the kernel with the following additional symbols:
   - ```CONFIG_DEBUG_FS```
   - ```CONFIG_GCOV_KERNEL```
   - ```CONFIG_GCOV_FORMAT_AUTODETECT```

 - Add

              GCOV_PROFILE_deadline.o := y

   to ```kernel/sched/Makefile```

 - On the target, mount debugfs if it is not yet mounted:

              mount -t debugfs none /sys/kernel/debug

 - Run the tests

 - Copy *.gcda and *.gcno files from ```/sys/kernel/debug/gcov/``` to your
   build machine e.g. in directory ```/tmp/gcov```

 - For gcov, enter the directory of the built kernel and type

              (your_toolchain)-gcov -o /tmp/gcov deadline.c

   Then, read the produced .gcov file

 - Alternatively, for lcov (frontend to gcov), enter the directory of the built
   kernel and type

              lcov -c --base-directory . -d /tmp/gcov/ --output-file coverage.info

              genhtml -o /tmp/coverage/ coverage.info

   Then, enter directory ```/tmp/coverage``` and open ```index.html```.

 - Note: currently, the tests cover **84%** of the ```deadline.c``` file
         (including the code executed at boot time by Linux).
