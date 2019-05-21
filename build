#!/bin/sh
#See LICENSE file for copyright and license details.

CPPFLAGS="-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2"
CFLAGS="-std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os $CPPFLAGS"
cc $CFLAGS test.c emdb.c -o test
