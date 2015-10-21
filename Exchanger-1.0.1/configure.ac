#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# $Id: configure.ac 15119 2009-06-04 18:42:40Z tan2 $

AC_PREREQ(2.59)
AC_INIT([Exchanger], [1.0.1], [cig-mc@geodynamics.org], [Exchanger])
AC_CONFIG_AUX_DIR([./aux-config])
AC_CONFIG_SRCDIR([Exchanger/Exchanger.py])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign])

# 'configure' options
AC_ARG_VAR(PYTHON, [Python interpreter])
AC_ARG_VAR(PYTHONPATH, [Python module search path])

# Check for Python.
AM_PATH_PYTHON([2.3])
CIT_PYTHON_SYSCONFIG

# Check for Python modules and packages.
CIT_PYTHON_EGG_SETUP

AC_SUBST([pythonegginfodir], [\${pythondir}/$PACKAGE.egg-info])

# Checks for programs.
AC_PROG_CXX([mpicxx mpic++ mpiCC hcp mpCC mpxlC mpxlC_r cmpic++ g++ c++ gpp aCC CC cxx cc++ cl FCC KCC RCC xlc++_r xlC_r xlC icpc ecpc pgCC])
AC_LANG(C++)
AC_DISABLE_SHARED
AC_PROG_LIBTOOL

# Checks for libraries.
AC_SEARCH_LIBS([MPI_Init], [mpi mpich], [], [AC_MSG_ERROR([MPI library not found])])

# Checks for header files.
CIT_HEADER_MPI

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

dnl end of configure.ac
