# -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
#-------------------------------------------
m4_define([libkxl_package_name], [libkxl])

# PACKAGE: Normally this is just major:minor
# and library CRA runs separately with three
# values independent of package major:minor.
#
# Making PACKAGE point releases:
#    libkxl_major_version += 0;
#    libkxl_minor_version += 1; (patches or added function(s))
#
# If any new functions have been added:
#    libkxl_major_version += 0;
#    libkxl_minor_version += 1; (added function(s))
#
# If backwards compatibility has been broken:
#    libkxl_major_version += 1;
#    libkxl_minor_version = 0;
#
m4_define([libkxl_major_version], '1')
m4_define([libkxl_minor_version], '2')
# next git tag point should be 1.3 instead of 1.2.5
# remove the ":4" seen below, when upgrading to 1.3
m4_define([libkxl_version],
          [libkxl_major_version.libkxl_minor_version.4])
#
# Libraries have a "libtool" version of form current:revision:age.
# To update the libtool version which should be set independently
# of the package's major:minor version, do the following steps:
#
# 1. If the code has changed at all
#    (e.g. an internal data update):
#    libkxl_revision += 1
#
# 2. If any interfaces have been added, removed, or changed
#    (e.g. a new function has been added):
#    libkxl_current += 1
#    libkxl_revision = 0
#
# 3. If any interfaces have been added:
#    libkxl_age += 1
#
# 4. If any interfaces have been removed or changed
#    (e.g. backwards compatibility has been broken):
#    libkxl_age = 0
#
m4_define([libkxl_current], ['0'])
m4_define([libkxl_revision],['0'])
m4_define([libkxl_age],     ['0'])
m4_define([libkxl_CRA],
          [libkxl_current:libkxl_revision:libkxl_age])

#-------------------------------------------
AC_INIT([kxl], [libkxl_version],
  [https://github.com/Quipyowert2/libKXL/issues],
  [libkxl_package_name],
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

dnl Checks for libraries.
dnl https://libcheck.github.io/check/
PKG_CHECK_MODULES([CHECK], [check >= 0.9.10])

dnl Checks for header files.
AC_PATH_XTRA
AC_HEADER_STDC
AC_CHECK_HEADERS(fcntl.h malloc.h sys/ioctl.h sys/time.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_TIME

dnl Checks for library functions.
AC_PROG_GCC_TRADITIONAL
AC_TYPE_SIGNAL
AC_CHECK_FUNCS(select)

aclocaldir='${datadir}/aclocal'
AC_SUBST(aclocaldir)

dnl Whether to enable fuzz testing
AC_ARG_ENABLE([fuzz],
  [AS_HELP_STRING([--enable-fuzz], [enable fuzz testing KXL_LoadBitmap
  @<:@default=no@:>@])],
  [fuzz=$enableval], [fuzz=no])

if test x"$fuzz" = xyes; then
  AC_DEFINE([FUZZ], [1], [Define if building fuzz program])
  AC_SUBST([FUZZ])
  AC_CONFIG_FILES([fuzz/Makefile])
fi
AM_CONDITIONAL([ENABLE_FUZZ], [test x"$fuzz" = xyes])

dnl Whether to enable unit testing
AC_ARG_ENABLE([test],
  [AS_HELP_STRING([--enable-test], [enable unit tests
  @<:@default=yes@:>@])],
  [test=$enableval], [test=yes])

if test x"$test" = xyes; then
  AC_DEFINE([TEST], [1], [Define if unit testing])
  AC_SUBST([TEST])
  AC_CONFIG_FILES([tests/Makefile])
fi

AM_CONDITIONAL([ENABLE_TEST], [test x"$test" = xyes])

#-------------------------------------------
# Pass some variables to MAKEFILE.AM
AC_SUBST([HOST], [$host])
AC_SUBST([LIBKXL_CRA], [$libkxl_CRA])

AC_CONFIG_FILES([
KXL.spec
Makefile
src/Makefile
docs/Makefile
libkxl.pc
])

AC_OUTPUT
