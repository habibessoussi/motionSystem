AC_INIT([motion_gateway_rpi], [1.0], [mohamedhabib.essoussi@gmail.com])


dnl Must come before AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE

# Minimum Autoconf version required.
AC_PREREQ(2.60)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.in])


dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC

# We need a C++ compiler 
AC_PROG_CXX

dnl Check for RANLIB
AC_PROG_RANLIB


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])


# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T


AC_CONFIG_FILES([Makefile
				src/Makefile])

AC_OUTPUT