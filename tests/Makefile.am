## Process this file with automake to produce Makefile.in

# The braces around ACLOCAL_FLAGS below instead of parentheses are intentional!
# Otherwise autoreconf misparses the line.
ACLOCAL_AMFLAGS =-I m4 ${ACLOCAL_FLAGS}
AM_CFLAGS	= ${CFLAGS} ${CPPFLAGS} ${X11_CFLAGS} ${PULSEAUDIO_CFLAGS}
AM_CPPFLAGS	= -I${top_builddir} -I${top_srcdir}/src -I${top_srcdir}/

# test this package library before doing an install
DEPS   = ${top_builddir}/src/libKXL.la
LDADDS = ${top_builddir}/src/libKXL.la

noinst_PROGRAMS = test_01 test_02 sample

TESTS = test_01 test_02 sample

test_01_SOURCES = test_01.c
test_01_LDADD = ${LDADDS}

test_02_SOURCES = test_02.c
test_02_LDADD = ${LDADDS}

sample_SOURCES = sample.c
sample_LDADD   = ${LDADDS}

EXTRA_DIST = sample.c test_01.c test_02.c test_bmp_PXIpZM
nodist_EXTRA_DATA = .deps .libs test_01 test_02 \
  sample sample.bc sample.o test-suite.log

clean-local:
	rm -f ${builddir}/test_01 ${builddir}/test_02 \
	${builddir}/sample ${builddir}/sample.bc ${builddir}/sample.o
