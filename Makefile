export CC=gcc
export CFLAGS=-std=c99 -Wall -Wextra -I $(PWD)/include/
export LDLIBS=-lrt -pthread

SUBDIRS := $(wildcard T0*/.)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

clean: $(SUBDIRS)

clean_data: $(SUBDIRS)

.PHONY: all $(SUBDIRS) clean clean_data

