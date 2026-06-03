# Makefile.am - Top level automakefile for libKXL

SUBDIRS = src tests docs

aclocaldir = @aclocaldir@
aclocal_DATA = m4/KXL.m4

DIST_SUBDIRS = src tests docs
EXTRA_DIST = AUTHORS COPYING NEWS README \
  ChangeLog KXL.spec.in README.md m4/KXL.m4 libKXL.pc.in
DISTCLEANFILES = ar-lib compile config.guess config.log config.sub \
  depcomp INSTALL install-sh libKXL.pc ltmain.sh missing \
  test-driver
nodist_EXTRA_DATA = .git .github

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ${builddir}/libKXL.pc

LIBTOOL_DEPS = @LIBTOOL_DEPS@

libtool: ${LIBTOOL_DEPS}
	${SHELL} ${builddir}/config.status libtool

clean-local:
	rm -f ${builddir}/libKXL.pc ${builddir}/KXL.spec
