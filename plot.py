#!/usr/bin/python
import sys
import re
import string
import os # Used for files
from subprocess import call

num_cpus=4
data = [("bw",      "bprint:",          "cpu=",     "new_bw="),
       #("freq",    "cpu_frequency:",   "cpu_id=",  "state="),
        ("freq",   "bprint:",          "cpu_id=",  "next_freq=")]

if len(sys.argv) == 1:
    print "Error: no file provided!"
    print "Usage: ", sys.argv[0], " <file>"
    sys.exit()

os.chdir(sys.argv[1])

# Read whole file
with open("trace.txt") as f:
    lines = f.readlines()

# Cycle on cpus
for cpu in range (0, num_cpus):

    # Cycle on values
    for val in range(0, len(data)):

        # Open file
        out_file_name = "plot_cpu" + str(cpu) + "_" + str(val) + ".txt"
        out_file = open(out_file_name, "w")
        out_file.truncate()
        out_file_header = "Time\t" + data[val][0] + "\n"
        out_file.write(out_file_header)

        # Cycle on lines
        for line in lines:

            # Filter cpu
            if data[val][2]+str(cpu) in line:
                fields = line.split()
                time = re.sub(r'[\.,:]', '', fields[2])
                event = fields[3]

                # Filter event
                if event == data[val][1]:

                    # Search field
                    reg = data[val][3] + "(.*)"
                    for field in fields:
                        field_search = re.search(reg, field, re.IGNORECASE)
                        if field_search:
                                value = field_search.group(1)
                                out_file.write(time + "\t" + value + "\n")

    out_file.close()
    gp_set_title = "\"TITLE='CPU " + str(cpu) + "'\""
    gp_set_max = "\"MAX='" + str(len(data)-1) + "'\""
    gp_set_cpu = "\"CPU_ID='" + str(cpu) + "'\""
    os.system ("gnuplot -e "+ gp_set_title + " -e " + gp_set_max + " -e " + gp_set_cpu + " ../plot.gp")
