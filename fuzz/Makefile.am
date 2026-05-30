DEPS =
bin_PROGRAMS =
sample_SOURCES =
sample_LDADD =
sample_CFLAGS =
sample_LDFLAGS =
FUZZ_TARGETS =

#sample.bc is LLVM IR bitcode
if ENABLE_FUZZ
DEPS += ${top_builddir}/src/libkxl.la
bin_PROGRAMS += sample
sample_SOURCES += sample.c ${top_builddir}/src/KXL.h
sample_LDADD += ${top_builddir}/src/libkxl.la
sample_CFLAGS += -g -O3 -I../src -L/usr/local/lib64
sample_LDFLAGS += -lX11 -lpulse-simple -lpulse
FUZZ_TARGETS += sample sample.bc sample.o
endif

EXTRA_DIST = sample.c test_bmp_PXIpZM
nodist_EXTRA_DATA = .deps .libs sample sample.bc sample.o

clean-local:
	rm -f ${builddir}/sample ${builddir}/sample.bc ${builddir}/sample.o
