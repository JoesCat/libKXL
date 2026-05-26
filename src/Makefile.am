lib_LTLIBRARIES = libKXL.la
libKXL_la_SOURCES = KXLmisc.c KXLsound.c KXLvisual.c KXLimage.c
include_HEADERS = KXL.h
libKXL_la_CFLAGS = -DUSE_PULSEAUDIO
libKXL_la_LDFLAGS = -lpulse-simple -version-info 0:0:0
libKXL_la_LIBADD = -L/usr/X11R6/lib -lX11
