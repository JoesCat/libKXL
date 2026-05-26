SUBDIRS = . src docs
if ENABLE_FUZZ
SUBDIRS += fuzz
endif
if ENABLE_TEST
SUBDIRS += tests
endif
aclocaldir = @aclocaldir@
aclocal_DATA = m4/KXL.m4
EXTRA_DIST = COPYING ChangeLog README KXL.m4
