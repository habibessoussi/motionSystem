AC_INIT([motionSystem], [1.0], [mohamedhabib.essoussi@gmail.com])

AC_CANONICAL_SYSTEM


dnl Must come before AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE

# Minimum Autoconf version required.
AC_PREREQ(2.60)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.in])

build_mcu=no
build_rpi=no

dnl Check for crosscompilation 

echo "HOST = $host"

case $host in
	arm-none-eabi) # The MCU embedded software
		AC_CONFIG_SUBDIRS([motion_detector_mcu]) 
		build_mcu=yes
	    ;;
	arm-unknown-linux-gnueabihf) # The Raspberry pi Linux embedded software
		AC_CONFIG_SUBDIRS([motion_gateway_rpi]) 
		build_rpi=yes
		;;
		*) # The CGI web application
		;;
esac

AM_CONDITIONAL(MAKE_MCU,[test x$build_mcu = xyes])
AM_CONDITIONAL(MAKE_RPI,[test x$build_rpi = xyes])


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



AC_CONFIG_FILES([Makefile])

AC_OUTPUT