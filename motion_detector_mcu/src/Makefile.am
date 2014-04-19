format=elf

bin_PROGRAMS=motion_detector_mcu.elf
		
motion_detector_mcu_elf_SOURCES=motion_detector_mcu.c \
							    mcu_init.c 


AM_CPPFLAGS=-I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx \
		    -I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/CoreSupport \
		    -I$(abs_top_srcdir)/STSW-STM32072/STM32L1xx_StdPeriph_Driver/inc \
		    -I$(srcdir)/../include -DUSE_STDPERIPH_DRIVER

motion_detector_mcu_elf_LDADD=-L$(top_builddir)/STSW-STM32072/STM32L1xx_StdPeriph_Driver/src -lstm32l1xx \
							  -L$(top_builddir)/STSW-STM32072/CMSIS/CM3/CoreSupport -lcoresupport \
							  -L$(top_builddir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx -lstm32system
							 
motion_detector_mcu_elf_LDFLAGS=-T$(srcdir)/stm32_flash.ld

CPFLAGS=-Obinary	
CP=arm-none-eabi-objcopy
  
deploy: $(bin_PROGRAMS)
		$(CP) $(CPFLAGS) $(bin_PROGRAMS) motion_detector_mcu.bin
	
install-exec-hook:
	cp motion_detector_mcu.bin @prefix@/bin
