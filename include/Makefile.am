include_HEADERS = \
	libcdirectory.h

pkginclude_HEADERS = \
	libcdirectory/codepage.h \
	libcdirectory/definitions.h \
	libcdirectory/error.h \
	libcdirectory/extern.h \
	libcdirectory/features.h \
	libcdirectory/types.h

EXTRA_DIST = \
	libcdirectory.h.in \
	libcdirectory/definitions.h.in \
	libcdirectory/features.h.in \
	libcdirectory/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libcdirectory.h
	-rm -f libcdirectory/definitions.h
	-rm -f libcdirectory/features.h
	-rm -f libcdirectory/types.h
	-rm -f Makefile

