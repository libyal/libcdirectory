MSVSCPP_FILES = \
	cdirectory_test_get_version/cdirectory_test_get_version.vcproj \
	libcdirectory/libcdirectory.vcproj \
	libcerror/libcerror.vcproj \
	libclocale/libclocale.vcproj \
	libcstring/libcstring.vcproj \
	libuna/libuna.vcproj \
	libcdirectory.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

