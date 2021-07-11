AC_INIT([gtkcairoplot], [0.0.1], [demfuhlseine-mail@gmx.de])
: ${CFLAGS="-O3"}

# Will be generated
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign no-dependencies subdir-objects])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Check if C-compiler supports c99 standard
AX_CHECK_C99_STD

AC_ARG_ENABLE(
   [debug],
   [AS_HELP_STRING([--enable-debug],[build with additional debugging code [default=no]])],
   [],
   [enable_debug="no"])
AM_CONDITIONAL([ENABLE_DEBUG], [test "$enable_debug" = yes])
AM_COND_IF(
   [ENABLE_DEBUG],
   [AX_APPEND_FLAG([-g])
    AX_APPEND_FLAG([-D_DEBUG])])

# check for gtk
PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.0])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT
