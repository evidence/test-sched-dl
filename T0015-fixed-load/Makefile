SRCS=$(wildcard *.c)
APP=$(shell basename `pwd`)

all: $(APP) calibrate

$(APP): main.c
	$(CC) $(CFLAGS) main.c -o $(APP) $(LDLIBS)

calibrate: calibrate.c
	$(CC) $(CFLAGS) calibrate.c -o calibrate $(LDLIBS)

.PHONY:clean clean_data

clean: clean_data
	-rm -fr $(APP) calibrate

clean_data:
	-rm -fr *.txt *.dat*
