AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDIRECTORY_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	cdirectory_test_directory \
	cdirectory_test_directory_entry \
	cdirectory_test_error \
	cdirectory_test_support

cdirectory_test_directory_SOURCES = \
	cdirectory_test_directory.c \
	cdirectory_test_libcdirectory.h \
	cdirectory_test_libcerror.h \
	cdirectory_test_libcstring.h \
	cdirectory_test_macros.h \
	cdirectory_test_memory.c cdirectory_test_memory.h \
	cdirectory_test_unused.h

cdirectory_test_directory_LDADD = \
	../libcdirectory/libcdirectory.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cdirectory_test_directory_entry_SOURCES = \
	cdirectory_test_directory_entry.c \
	cdirectory_test_libcdirectory.h \
	cdirectory_test_libcerror.h \
	cdirectory_test_libcstring.h \
	cdirectory_test_macros.h \
	cdirectory_test_memory.c cdirectory_test_memory.h \
	cdirectory_test_unused.h

cdirectory_test_directory_entry_LDADD = \
	../libcdirectory/libcdirectory.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cdirectory_test_error_SOURCES = \
	cdirectory_test_error.c \
	cdirectory_test_libcdirectory.h \
	cdirectory_test_libcerror.h \
	cdirectory_test_libcstring.h \
	cdirectory_test_macros.h \
	cdirectory_test_unused.h

cdirectory_test_error_LDADD = \
	../libcdirectory/libcdirectory.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

cdirectory_test_support_SOURCES = \
	cdirectory_test_libcdirectory.h \
	cdirectory_test_libcstring.h \
	cdirectory_test_macros.h \
	cdirectory_test_support.c \
	cdirectory_test_unused.h

cdirectory_test_support_LDADD = \
	../libcdirectory/libcdirectory.la \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

