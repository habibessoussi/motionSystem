AC_INIT([motion_detector_mcu], [1.0], [mohamedhabib.essoussi@gmail.com])

dnl Must come before AM_INIT_AUTOMAKE.
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Minimum Autoconf version required.
AC_PREREQ(2.60)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.in])

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC


AM_PROG_CC_C_O

dnl for assembler startup files
AM_PROG_AS

dnl Check for RANLIB
AC_PROG_RANLIB

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 STSW-STM32072/Makefile
				 STSW-STM32072/STM32L1xx_StdPeriph_Driver/Makefile
				 STSW-STM32072/STM32L1xx_StdPeriph_Driver/src/Makefile
				 STSW-STM32072/CMSIS/Makefile
				 STSW-STM32072/CMSIS/CM3/Makefile
				 STSW-STM32072/CMSIS/CM3/CoreSupport/Makefile
				 STSW-STM32072/CMSIS/CM3/DeviceSupport/Makefile
				 STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/Makefile
				 STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx/Makefile])


AC_OUTPUT