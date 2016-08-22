AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDIRECTORY_DLL_IMPORT@

TESTS = \
	test_api_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cdirectory_test_get_version

cdirectory_test_get_version_SOURCES = \
	cdirectory_test_get_version.c \
	cdirectory_test_libcdirectory.h \
	cdirectory_test_libcstring.h \
	cdirectory_test_macros.h \
	cdirectory_test_unused.h

cdirectory_test_get_version_LDADD = \
	../libcdirectory/libcdirectory.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

