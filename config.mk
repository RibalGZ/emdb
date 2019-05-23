#See LICENSE file for copyright and license details.
VERSION = 0

PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
HEADDIR = $(PREFIX)/include

LIBSHORT = libemdb.so
LIBNAME = ${LIBSHORT}.0.0.0
LIBSONAME = ${LIBSHORT}.0

CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\"
CFLAGS = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${CPPFLAGS}
FPIC = -fPIC
LDFLAGS = ${FPIC} -shared -Wl,-soname,${LIBSONAME}

# compiler and linker
CC = cc
