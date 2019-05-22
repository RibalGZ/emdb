#See LICENSE file for copyright and license details.

TESTBIN := test

TESTSRC := $(wildcard *.c)
TESTOBJ := $(TESTSRC:%.c=%.o)

PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib
HEADDIR ?= $(PREFIX)/include

CPPFLAGS := -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2
CFLAGS := -std=c99 -pedantic -Wall -Wno-deprecated-declarations -L../ -I../ -L$(LIBDIR) -I$(HEADDIR) $(CPPFLAGS)

.PHONY: clean purge

$(TESTBIN): $(TESTOBJ)
	cc $(CFLAGS) $^ -o $@ -lemdb

%.o: %.c
	cc $(CFLAGS) -c $<

clean:
	rm *.o

purge: clean
	rm test
