format=elf

bin_PROGRAMS=motion_detector_mcu.elf
		
motion_detector_mcu_elf_SOURCES=motion_detector_mcu.c \
							    mcu_init.c \
							    mcu_utils.c \
							    $(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx/startup/TrueSTUDIO/startup_stm32l1xx_md.s
							    


AM_CPPFLAGS=-I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx \
		    -I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/CoreSupport \
		    -I$(abs_top_srcdir)/STSW-STM32072/STM32L1xx_StdPeriph_Driver/inc \
		    -I$(srcdir)/../include -DUSE_STDPERIPH_DRIVER

motion_detector_mcu_elf_LDADD=-L$(top_builddir)/STSW-STM32072/STM32L1xx_StdPeriph_Driver/src -lstm32l1xx \
							  -L$(top_builddir)/STSW-STM32072/CMSIS/CM3/CoreSupport -lcoresupport \
							  -L$(top_builddir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx -lstm32system
							 
motion_detector_mcu_elf_LDFLAGS=-T$(srcdir)/stm32_flash.ld  \
								 -Xlinker -o$(bin_PROGRAMS) -Xlinker -M \
								 -Xlinker -Map=motion_detector_mcu.map -Xlinker --gc-sections

CPFLAGS=-O binary	
CP=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump -Sdl

install-exec-hook: $(bin_PROGRAMS)
		$(CP) $(CPFLAGS) $(bin_PROGRAMS) motion_detector_mcu.bin
		$(OBJDUMP) $(bin_PROGRAMS) > motion_detector_mcu.s
	    cp motion_detector_mcu.bin @prefix@/bin
