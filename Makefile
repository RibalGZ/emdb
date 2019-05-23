#See LICENSE file for copyright and license details.
include config.mk

LIBSRC = emdb.c
LIBOBJ = ${LIBSRC:.c=.o}

.PHONY: clean install

all: options ${LIBNAME}

options:
	@echo ${LIBNAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

${LIBNAME}: ${LIBOBJ}
	${CC} ${CFLAGS} ${LDFLAGS} $^ -o $@
	ln -fs ${LIBNAME} ${LIBSHORT}
	ln -fs ${LIBNAME} ${LIBSONAME}

%.o: %.c
	${CC} ${CFLAGS} ${FPIC} -c $<

install:
	install -m 644 emdb.h ${DESTDIR}${HEADDIR}/emdb.h
	install -m 755 ${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBNAME}
	ln -fs ${DESTDIR}${LIBDIR}/${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBSHORT}
	ln -fs ${DESTDIR}${LIBDIR}/${LIBNAME} ${DESTDIR}${LIBDIR}/${LIBSONAME}
	ldconfig

clean:
	rm -f libemdb.* ${LIBOBJ}
