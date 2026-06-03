## Process this file with automake to produce Makefile.in

# The braces around ACLOCAL_FLAGS below instead of parentheses are intentional!
# Otherwise autoreconf misparses the line.
ACLOCAL_AMFLAGS =-I m4 ${ACLOCAL_FLAGS}
AM_CFLAGS	= ${CFLAGS} ${CPPFLAGS} ${X11_CFLAGS} ${PULSEAUDIO_CFLAGS}
AM_CPPFLAGS	= -I${top_builddir} -I${top_srcdir}/src -I${top_srcdir}/

# test this package library before doing an install
DEPS   = ${top_builddir}/src/libKXL.la
LDADDS = ${top_builddir}/src/libKXL.la

noinst_PROGRAMS = check_foo sample

TESTS = check_foo sample
check_PROGRAMS    = check_foo
check_foo_SOURCES = test_001.c
check_foo_CFLAGS  = @CHECK_CFLAGS@ --coverage
check_foo_LDADD   = @CHECK_LIBS@ ${LDADDS}
check_foo_LDFLAGS = --coverage

sample_SOURCES = sample.c
sample_LDADD   = ${LDADDS}

EXTRA_DIST = sample.c test_001.c test_bmp_PXIpZM
nodist_EXTRA_DATA = .deps .libs check* test_001 \
  sample sample.bc sample.o test-suite.log

clean-local:
	rm -f ${builddir}/check* ${builddir}/test001 \
	${builddir}/sample ${builddir}/sample.bc ${builddir}/sample.o
