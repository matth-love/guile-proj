## Process this file with automake to produce Makefile.in

guileextension_LTLIBRARIES= libguile-proj.la

libguile_proj_la_SOURCES = guile_proj.c

libguile_proj_la_CPPFLAGS = $(GUILE_CFLAGS)

if WARN
libguile_proj_la_CPPFLAGS += -Wall -Wextra -Wstrict-prototypes	\
-Wmissing-prototypes -Wpointer-arith -Wreturn-type -Wcast-qual		\
-Wswitch -Wshadow -Wcast-align -Wwrite-strings -Wchar-subscripts	\
-Winline -Wnested-externs -Wredundant-decls -Wunused -Wformat=2
endif

if BUILDING_DLL
libguile_proj_la_CPPFLAGS += -DGUCU_DLL -DGUCU_DLL_EXPORTS
endif

libguile_proj_la_LDFLAGS = -no-undefined -version-info	\
$(LIBGUILE_PROJ_INTERFACE) $(GUILE_LDFLAGS)

if !DLL_VERSION_INFO
libguile_proj_la_LDFLAGS += -avoid-version
endif

### scheme files ###
pkgguilesitedir = $(guilesitedir)/proj
dist_pkgguilesite_DATA = proj.scm

### compiled scheme files ###

pkgguileobjectdir = $(guileobjectdir)/proj
pkgguileobject_DATA = $(dist_pkgguilesite_DATA:%.scm=%.go)

$(pkgguileobject_DATA): libguile-proj.la

GUILEC_FLAGS = -Warity-mismatch -Wformat -Wunused-variable

.scm.go:
	GUILE_AUTO_COMPILE=0 \
	LTDL_LIBRARY_PATH=$(abs_builddir)/.libs \
	$(GUILD) compile --target="$(host)" $(GUILEC_FLAGS) \
	 -L "$(abs_builddir)/.." -L "$(abs_srcdir)/.." -o "$@" "$<"

ETAGS_ARGS = proj.scm

CLEANFILES = $(pkgguileobject_DATA)
