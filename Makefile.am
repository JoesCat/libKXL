# Makefile.am - Top level automakefile for libkxl

SUBDIRS = src tests docs

aclocaldir = @aclocaldir@
aclocal_DATA = m4/KXL.m4

DIST_SUBDIRS = src tests docs
EXTRA_DIST = AUTHORS COPYING NEWS README \
  ChangeLog KXL.spec.in README.md m4/KXL.m4 libkxl.pc.in
DISTCLEANFILES = ar-lib compile config.guess config.log config.sub \
  depcomp INSTALL install-sh libkxl.pc ltmain.sh missing \
  test-driver
nodist_EXTRA_DATA = .git .github

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ${builddir}/libkxl.pc

LIBTOOL_DEPS = @LIBTOOL_DEPS@

libtool: ${LIBTOOL_DEPS}
	${SHELL} ${builddir}/config.status libtool

clean-local:
	rm -f ${builddir}/libkxl.pc ${builddir}/KXL.spec
