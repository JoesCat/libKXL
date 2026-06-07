# -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
#-------------------------------------------
m4_define([libKXL_package_name], [libKXL])

# PACKAGE: Normally this is just major:minor
# and library CRA runs separately with three
# values independent of package major:minor.
#
# Making PACKAGE point releases:
#    libKXL_major_version += 0;
#    libKXL_minor_version += 1; (patches or added function(s))
#
# If any new functions have been added:
#    libKXL_major_version += 0;
#    libKXL_minor_version += 1; (added function(s))
#
# If backwards compatibility has been broken:
#    libKXL_major_version += 1;
#    libKXL_minor_version = 0;
#
m4_define([libKXL_major_version], '1')
m4_define([libKXL_minor_version], '2')
# next git tag point should be 1.3 instead of 1.2.5
# remove the ":4" seen below, when upgrading to 1.3
m4_define([libKXL_version],
          [libKXL_major_version.libKXL_minor_version.4])
#
# Libraries have a "libtool" version of form current:revision:age.
# To update the libtool version which should be set independently
# of the package's major:minor version, do the following steps:
#
# 1. If the code has changed at all
#    (e.g. an internal data update):
#    libKXL_revision += 1
#
# 2. If any interfaces have been added, removed, or changed
#    (e.g. a new function has been added):
#    libKXL_current += 1
#    libKXL_revision = 0
#
# 3. If any interfaces have been added:
#    libKXL_age += 1
#
# 4. If any interfaces have been removed or changed
#    (e.g. backwards compatibility has been broken):
#    libKXL_age = 0
#
m4_define([libKXL_current], ['0'])
m4_define([libKXL_revision],['0'])
m4_define([libKXL_age],     ['0'])
m4_define([libKXL_CRA],
          [libKXL_current:libKXL_revision:libKXL_age])

#-------------------------------------------
AC_INIT([kxl], [libKXL_version],
  [https://github.com/Quipyowert2/libKXL/issues],
  [libKXL_package_name],
  [https://https://github.com/Quipyowert2/libKXL])
AC_CONFIG_SRCDIR([src/KXL.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE

#-------------------------------------------
# automake 1.12 seems to require AM_PROG_AR,
# but automake 1.11 doesn't recognize it.
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_MAKE_SET
AC_PROG_SED

#-------------------------------------------
# I am going to try enabling silent-rules by
# default so builders are more likely to see
# warnings *** Use --disable-silent-rules or
# "make V=1" if you need to see the rules.
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],
  [AC_SUBST([AM_DEFAULT_VERBOSITY],[1])])

#-------------------------------------------
# Checks for packages and libraries.
PKG_CHECK_MODULES([X11], [x11 >= 1.6.4],,
  [AC_MSG_ERROR([Please install the libX11 or lib64X11 development package, then try again])])
AC_SUBST([X11_CFLAGS])
AC_SUBST([X11_LIBS])

AC_ARG_ENABLE([pipewire],
  [AS_HELP_STRING([--disable-pipewire], [disable Pipewire Audio sound output @<:@default=no@:>@])],
  [pipewire=$enableval], [pipewire=yes])

AC_ARG_ENABLE([pulseaudio],
  [AS_HELP_STRING([--enable-pulseaudio], [enable PulseAudio sound output @<:@default=no@:>@])],
  [pulseaudio=$enableval], [pulseaudio=no])

PIPEWIREAUDIO_CFLAGS=
PIPEWIREAUDIO_LIBS=
PULSEAUDIO_CFLAGS=
PULSEAUDIO_LIBS=
if test x"$pipewire" = xyes; then
  # Prefer to build with pipewire instead of (obsolete) pulseaudio
  PKG_CHECK_MODULES([PIPEWIREAUDIO], [libpipewire-0.3 >= 0.3.19],,
    [AC_MSG_ERROR([Please install the libpipewire or lib64pipewire pulse development package, then try again])])
  AC_DEFINE([USE_PIPEWIREAUDIO], [1], [libKXL Sound uses the Pipewire Pulseaudio module])
  pulseaudio=no
  AC_CHECK_HEADERS(pipewire/pipewire.h)
fi
if test x"$pulseaudio" = xyes; then
  PKG_CHECK_MODULES([PULSEAUDIO], [libpulse-simple >= 14.2],,
    [AC_MSG_ERROR([Please install the libpulseaudio or lib64pulseaudio development package, then try again])])
  AC_DEFINE([USE_PULSEAUDIO], [1], [libKXL Sound uses the Pulseaudio pulse-simple module])
  AC_CHECK_HEADERS(pulse/simple.h)
fi
AM_CONDITIONAL([USE_PIPEWIREAUDIO], [test x"$pipewire" = xyes])
AC_SUBST([PIPEWIREAUDIO_CFLAGS])
AC_SUBST([PIPEWIREAUDIO_LIBS])
AM_CONDITIONAL([USE_PULSEAUDIO], [test x"$pulseaudio" = xyes])
AC_SUBST([PULSEAUDIO_CFLAGS])
AC_SUBST([PULSEAUDIO_LIBS])

dnl Checks for header files.
AC_CONFIG_HEADERS([src/KXL-config.h])
AC_CHECK_HEADERS(fcntl.h malloc.h sys/ioctl.h sys/time.h)

dnl Checks for library functions.
AC_CHECK_FUNCS(select)

aclocaldir='${datadir}/aclocal'
AC_SUBST(aclocaldir)

#-------------------------------------------
# Pass some variables to MAKEFILE.AM
AC_SUBST([HOST], [$host])
AC_SUBST([LIBKXL_CRA], [$libKXL_CRA])

#-------------------------------------------
# Put ifdef wrapper around KXL-config.h that
# it's not accidently called twice.
AH_TOP([#ifndef _KXL_CONFIG_H
#define _KXL_CONFIG_H 1])
AH_BOTTOM([#endif])

#-------------------------------------------
AC_CONFIG_FILES([
KXL.spec
Makefile
src/Makefile
tests/Makefile
docs/Makefile
libKXL.pc
])

AC_OUTPUT
