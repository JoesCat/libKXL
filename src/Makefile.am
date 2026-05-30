ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

include_HEADERS = KXL.h

lib_LTLIBRARIES = libkxl.la

libkxl_la_SOURCES = KXLmisc.c KXLsound.c KXLvisual.c KXLimage.c
libkxl_la_CFLAGS = -DUSE_PULSEAUDIO
libkxl_la_LDFLAGS = -lpulse-simple -version-info $(LIBKXL_CRA)
libkxl_la_LIBADD = -L/usr/X11R6/lib -lX11
libkxl_la.$(OBJEXT): KXL.h

EXTRA_DIST = KXL.h KXLmisc.c KXLsound.c KXLvisual.c KXLimage.c
