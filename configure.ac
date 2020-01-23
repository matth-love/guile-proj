i# ----------------------------------------------------------------
# configure.ac

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

# Process this file with autoconf to produce a configure script

##################
# Package info
AC_INIT([Guile-Proj],[0.2.3],[matthew.love@colorado.edu])

AC_CONFIG_AUX_DIR([build_aux])
AM_INIT_AUTOMAKE([gnu std-options -Wall])

AC_PREREQ(2.60)
AC_USE_SYSTEM_EXTENSIONS([_GNU_SOURCE])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])

##################
# Set the library libtool version constant
LIBGUILE_PROJ_INTERFACE="11:1:0"
AC_SUBST(LIBGUILE_PROJ_INTERFACE)

##################
# Check for Programs
PKG_PROG_PKG_CONFIG
AC_PROG_CC
AC_CANONICAL_HOST
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AM_PROG_AR

# from guile.m4
# sets: GUILE_CFLAGS and GUILE_LDFLAGS
GUILE_PKG([2.2 2.0])
GUILE_PROGS
GUILE_FLAGS
GUILE_SITE_DIR

AC_MSG_CHECKING([the Guile effective version])
guile_effective_version="`$GUILE -c '(display (effective-version))'`"
AC_MSG_RESULT([$guile_effective_version])

if test "x$GUILD" = "x"; then
   AC_MSG_WARN(['guild' binary not found; please check your guile-2.x installation.])
   AC_PATH_PROG([GUILD], guild)
fi

################
# Guile has three directories that don't follow the GNU Filesystem
# Heirarchy Standards.  If one follows the GNU FHS, files get installed
# in directories in which Guile does not search for them by default.
AC_ARG_WITH([gnu-filesystem-hierarchy],
            [AS_HELP_STRING([--with-gnu-filesystem-hierarchy],
                            [Strictly follow GNU Filesystem Heirarchy when installing, instead of querying Guile to discover the install directories that it expects.])])

case "x$with_gnu_filesystem_hierarchy" in
     xyes)
       # Follow the GNU Filesystem Heirarchy Standard correctly
       # Installed .scm scheme libraries go here
       AC_MSG_CHECKING([Guile site directory])
       guilesitedir="\$(datadir)/guile/site/$guile_effective_version"
       AC_MSG_RESULT([$guilesitedir])
       AC_SUBST(guilesitedir)

       # Compiled libguile-*.so extension libraries go here
       AC_MSG_CHECKING([Guile extension directory])
       guileextensiondir="$libdir/guile/$guile_effective_version"
       AC_MSG_RESULT([$guileextensiondir])
       AC_SUBST(guileextensiondir)

       # Compiled .go scheme libraries go here
       AC_MSG_CHECKING([Guile object directory])
       guileobjectdir="$libdir/guile/$guile_effective_version/site-ccache"
       AC_MSG_RESULT([$guileobjectdir])
       AC_SUBST(guileobjectdir)
       ;;
     *)
       # Get the installation directories from Guile
       # Installed .scm scheme libraries go here
       AC_MSG_CHECKING([Guile site directory])
       guilesitedir=$GUILE_SITE
       AC_MSG_RESULT([$guilesitedir])
       AC_SUBST(guilesitedir)

       # Compiled libguile-*.so extension libraries go here
       AC_MSG_CHECKING([Guile extension directory])
       guileextensiondir=$GUILE_EXTENSION
       AC_MSG_RESULT([$guileextensiondir])
       AC_SUBST(guileextensiondir)

       # Compiled .go scheme libraries go here
       AC_MSG_CHECKING([Guile object directory])
       guileobjectdir=$GUILE_SITE_CCACHE
       AC_MSG_RESULT([$guileobjectdir])
       AC_SUBST(guileobjectdir)
       ;;
esac

AC_CHECK_LIB([guile-$guile_effective_version], scm_make_foreign_object_type,
              [have_foreign_obj=yes],
              [have_foreign_obj=no])

if test "$have_foreign_obj" = "no"; then
AC_MSG_WARN([libguile foreign objects were not found, falling back to smobs])
fi

AM_CONDITIONAL([HAVE_FOREIGN_OBJ],[test "$have_foreign_obj" = yes])
AC_MSG_NOTICE([checking for proj])

have_proj_h=no
have_projects_h=no
dnl have_geodesic_h=no

AC_CHECK_LIB([proj], pj_init, [], [
		       echo "proj4 is required..."
		       exit -1])

AC_CHECK_HEADER([proj_api.h],	
                  [AC_DEFINE([HAVE_PROJ_H],
                             [1],
                             [Define if you have proj.h])],
                  [AC_MSG_FAILURE([proj.h could not be found])])

AC_CHECK_HEADER([projects.h],	
                  [AC_DEFINE([HAVE_PROJECTS_H],
                             [1],
                             [Define if you have projects.h])],
                  [AC_MSG_FAILURE([projects.h could not be found])])

dnl AC_CHECK_HEADER([geodesic.h],	
dnl                   [AC_DEFINE([HAVE_GEODESIC_H],
dnl                              [1],
dnl                              [Define if you have geodesic.h])],
dnl                   [AC_MSG_FAILURE([geodesic.h could not be found])])

##################
# Check for Libtool

# New method for when Libtool 2.x is default
LT_INIT([dlopen disable-fast-install disable-static win32-dll])


##################
# Initial guess of platform specific options

case $host_os in
mingw* | cygwin* | os2* | pw32* | cegcc*)
	[building_dll=yes] ;;
*)
	[building_dll=no] ;;
esac
case $host_os in
mingw* | os2* | pw32* | cegcc*)
	[building_shell=no] ;;
*)
	[building_shell=yes] ;;
esac
case $host_os in
mingw* )
	[dll_version_info=no] ;;
*)
	[dll_version_info=yes] ;;
esac

AM_CONDITIONAL([BUILDING_DLL], [test "$building_dll" = yes])
AM_CONDITIONAL([BUILDING_SHELL], [test "$building_shell" = yes])
AM_CONDITIONAL([DLL_VERSION_INFO], [test "$dll_version_info" = yes])

##################
# Check for libraries

AC_ARG_ENABLE([warnings],
              [AS_HELP_STRING([--enable-warnings],
                              [Build with most GCC warnings enabled])])
AM_CONDITIONAL([WARN], [test "$enable_warnings" = yes])

##################
# Check for header files
AC_CHECK_HEADERS([ctype.h])

##################
#  Output

AC_CONFIG_FILES([Makefile src/Makefile src/proj/Makefile examples/Makefile scripts/Makefile])

if test "$have_foreign_obj" = "no"; then
AC_CONFIG_FILES([src_dep/Makefile])
fi

AC_OUTPUT

if test "$with_gnu_filesystem_hierarchy" = "yes"; then
   # Guile has a different prefix than this module
   AC_MSG_WARN([]
   [The Guile modules will be installed in $guilesitedir.]
   [The Guile extension libraries will be installed in $guileextensiondir.]
   [The compiled modules will be installed in $guileobjectdir.]
   [This is because you ran configure with the `--with-gnu-filesystem-hierarchy' flag]
   []
   [Remember that you will have to adjust the `GUILE_LOAD_PATH' environment]
   [variable.])
else
   AC_MSG_NOTICE([]
   [The Guile modules will be installed in $guilesitedir.]
   [The Guile extension libraries will be installed in $guileextensiondir.]
   [The compiled modules will be installed in $guileobjectdir.]
   [These directories are the ones expected by $GUILE])
fi
AC_SUBST([guilesitedir])

