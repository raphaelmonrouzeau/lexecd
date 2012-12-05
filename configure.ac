#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([lexec], [0.0.1], [raphael.monrouzeau@gmail.com])
AM_INIT_AUTOMAKE(lexec, 0.0.1)
# Store auxiliary scripts in
#AC_CONFIG_AUX_DIR([build-aux])
AC_OUTPUT(Makefile src/Makefile src/lexecd/Makefile src/lxd_check/Makefile doc/Makefile examples/Makefile man/Makefile scripts/Makefile)

AC_CONFIG_SRCDIR([src/lexecd/lexecd.c])

# Configure header file
AC_CONFIG_HEADERS([src/config.h])
#AC_DEFINE(VARIABLE, VALUE, DESCRIPTION)

# Configure Makefile
#AC_SUBST(VARIABLE, [VALUE])

# Checks for programs.
AC_PROG_CC
#AC_PROG_CXX
#AC_PROG_F77
#AC_PROG_SED
#AC_PROG_YACC
#AC_PROG_LEX
#AC_CHECK_PROGS([TAR], [tar gtar], [:])
#if test "$TAR" = :; then
#    AC_MSG_ERROR([This package needs tar.])
#    AC_MSG_WARN([This package needs tar.])
#fi

# Checks for libraries.
#AC_CHECK_LIB([efence], [malloc], [EFENCELIB=-lefence])
#AC_SUBST([EFENCELIB])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_C_RESTRICT

# Checks for library functions.

AC_OUTPUT
