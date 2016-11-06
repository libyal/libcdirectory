include_HEADERS = \
	libcdirectory.h

pkginclude_HEADERS = \
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
	/bin/rm -f libcdirectory.h
	/bin/rm -f libcdirectory/definitions.h
	/bin/rm -f libcdirectory/features.h
	/bin/rm -f libcdirectory/types.h
	/bin/rm -f Makefile

