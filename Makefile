#See LICENSE file for copyright and license details.

LIBSHORT := libemdb.so
LIBNAME := ${LIBSHORT}.0.0.0
LIBSONAME := ${LIBSHORT}.0

LIBSRC := $(wildcard *.c)
LIBOBJ := $(LIBSRC:%.c=%.o)

PREFIX ?= /usr/local
LIBDIR ?= ${PREFIX}/lib
HEADDIR ?= ${PREFIX}/include

CPPFLAGS := -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2
CFLAGS := -std=c99 -pedantic -Wall -Wno-deprecated-declarations ${CPPFLAGS}
FPIC := -fPIC
LDFLAGS := ${FPIC} -shared -Wl,-soname,${LIBSONAME}

.PHONY: clean purge install

${LIBNAME}: ${LIBOBJ}
	cc ${CFLAGS} ${LDFLAGS} $^ -o $@ -lc
	ln -fs ${LIBNAME} ${LIBSHORT}
	ln -fs ${LIBNAME} ${LIBSONAME}

%.o: %.c
	cc ${CFLAGS} ${FPIC} -c $<

install:
	install -m 644 emdb.h ${DESTDIR}${HEADDIR}/emdb.h

	install -m 755 ${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBNAME}
	ln -fs ${DESTDIR}${LIBDIR}/${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBSHORT}
	ln -fs ${DESTDIR}${LIBDIR}/${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBSONAME}
	ldconfig

clean:
	rm *.o

purge: clean
	rm libemdb.*
