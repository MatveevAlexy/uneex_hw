#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Guesser with romans], [0.0.1], [BUG-REPORT-ADDRESS], [guess])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guess])
AC_CONFIG_SRCDIR([guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([
    Makefile
    Doxyfile
])
AC_OUTPUT
