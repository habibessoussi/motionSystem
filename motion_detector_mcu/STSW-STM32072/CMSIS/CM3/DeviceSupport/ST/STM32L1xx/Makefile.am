noinst_LIBRARIES=libstm32system.a

libstm32system_a_SOURCES=system_stm32l1xx.c \
						 startup/gcc_ride7/startup_stm32l1xx_md.s


AM_CPPFLAGS=-I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx \
		    -I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/CoreSupport \
		    -I$(abs_top_srcdir)/STSW-STM32072/STM32L1xx_StdPeriph_Driver/inc \
		    -I$(srcdir)/../ -DUSE_STDPERIPH_DRIVER