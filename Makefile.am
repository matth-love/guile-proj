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

# Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4 --install
AM_DISTCHECK_CONFIGURE_FLAGS = --with-gnu-filesystem-hierarchy

# Additional files to distribute
# EXTRA_DIST = README.cygwin README.mingw README.openbsd

if HAVE_FOREIGN_OBJ
SUBDIRS = src examples scripts
else
SUBDIRS = src_dep
endif
