## Process this file with automake to produce Makefile.in

# The braces around ACLOCAL_FLAGS below instead of parentheses are intentional!
# Otherwise (older) autoreconf misparses this line.
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

include_HEADERS = KXL.h

lib_LTLIBRARIES = libKXL.la

libKXL_la_SOURCES = KXLmisc.c KXLsound.c KXLjoystick.c KXLvisual.c KXLimage.c
libKXL_la_CFLAGS  = ${X11_CFLAGS} ${PIPEWIREAUDIO_CFLAGS} ${PULSEAUDIO_CFLAGS}
libKXL_la_LDFLAGS = -no-undefined -version-info ${LIBKXL_CRA}
libKXL_la_LIBADD  = ${X11_LIBS} ${PIPEWIREAUDIO_LIBS} ${PULSEAUDIO_LIBS}
libKXL_la.$(OBJEXT): KXL.h

EXTRA_DIST = KXL.h KXLmisc.c KXLsound.c KXLjoystick.c KXLvisual.c KXLimage.c
