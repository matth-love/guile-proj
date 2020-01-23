# ----------------------------------------------------------------
# Makefile.am 

# This file is part of GUILE-PROJ

# Copyright (C) 2018 by Matthew Love <matthew.love@colorado.edu>
# GUILE-PROJ is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# GUILE-PROJ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with GUILE-PROJ.  If not, see <http://www.gnu.org/licenses/>.

# --------------------------------------------------------------

## Process this file with automake to produce Makefile.in

snarfcppopts = $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
SUFFIXES: .x
.c.x:
	guile-snarf -o $@ $< $(snarfcppopts)

guileextension_LTLIBRARIES= libguile-proj.la

##libguile_proj_la_SOURCES = geodesic_guile.c proj_guile.c
libguile_proj_la_SOURCES = proj_guile.c

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
## dist_pkgguilesite_DATA = projects.scm geodesic.scm
dist_pkgguilesite_DATA = projects.scm

### compiled scheme files ###

pkgguileobjectdir = $(guileobjectdir)/proj
pkgguileobject_DATA = $(dist_pkgguilesite_DATA:%.scm=%.go)

$(pkgguileobject_DATA): libguile-proj.la

GUILEC_FLAGS = -Warity-mismatch -Wformat -Wunused-variable
guilec_opts = --load-path=$(abs_top_srcdir)/src/
.scm.go:
	GUILE_AUTO_COMPILE=0 \
	LTDL_LIBRARY_PATH=$(abs_builddir)/.libs \
	$(GUILD) compile --target="$(host)" $(GUILEC_FLAGS) $(guilec_opts)\
	 -L "$(abs_builddir)/.." -L "$(abs_srcdir)/.." -o "$@" "$<"

## ETAGS_ARGS = projects.scm geodesic.scm
ETAGS_ARGS = projects.scm

CLEANFILES = $(pkgguileobject_DATA)
