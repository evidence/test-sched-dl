SRCS=$(wildcard *.c)
APP=$(shell basename `pwd`)

all: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(APP) $(LDLIBS)

.PHONY:clean clean_data

clean: clean_data
	-rm -fr $(APP)

clean_data:
	-rm -fr *.txt *.dat*
