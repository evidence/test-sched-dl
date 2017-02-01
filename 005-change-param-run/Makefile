SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
APPS=$(SRCS:.c=)

all: $(APPS)

.PHONY:clean clean_data

clean: clean_data
	-rm -fr $(OBJS) $(APPS)

clean_data:
	-rm -fr *.txt *.dat*
