ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	include \
	common \
	libcerror \
	libclocale \
	libuna \
	libcdirectory \
	po \
	manuals \
	tests \
	msvscpp

DPKG_FILES = \
	dpkg/changelog \
	dpkg/changelog.in \
	dpkg/compat \
	dpkg/control \
	dpkg/copyright \
	dpkg/rules \
	dpkg/libcdirectory-dev.install \
	dpkg/libcdirectory.install \
	dpkg/source/format

GETTEXT_FILES = \
	config.rpath \
	po/Makevars.in

PKGCONFIG_FILES = \
	libcdirectory.pc.in

SPEC_FILES = \
	libcdirectory.spec \
	libcdirectory.spec.in

EXTRA_DIST = \
	$(DPKG_FILES) \
	$(GETTEXT_FILES) \
	$(PKGCONFIG_FILES) \
	$(SPEC_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

pkgconfigdir = $(libdir)/pkgconfig

pkgconfig_DATA = \
	libcdirectory.pc

libtool: @LIBTOOL_DEPS@
	cd $(srcdir) && $(SHELL) ./config.status --recheck

lib: library

library:
	cd $(srcdir)/common && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcerror && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libclocale && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libuna && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/libcdirectory && $(MAKE) $(AM_MAKEFLAGS)
	cd $(srcdir)/po && $(MAKE) $(AM_MAKEFLAGS)

distclean: clean
	-rm -f Makefile
	-rm -f config.status
	-rm -f config.cache
	-rm -f config.log
	-rm -f libcdirectory.pc
	-rm -f libcdirectory.spec
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE) distclean) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

