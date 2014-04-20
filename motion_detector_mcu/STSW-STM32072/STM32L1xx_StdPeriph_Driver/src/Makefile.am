noinst_LIBRARIES=libstm32l1xx.a

libstm32l1xx_a_SOURCES=\
					   stm32l1xx_gpio.c \
					   stm32l1xx_lcd.c \
					   stm32l1xx_exti.c \
					   stm32l1xx_syscfg.c \
					   stm32l1xx_pwr.c \
					   stm32l1xx_rcc.c \
					   stm32l1xx_rtc.c \
					   stm32l1xx_usart.c \
					   misc.c
					   
AM_CPPFLAGS=-I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/DeviceSupport/ST/STM32L1xx \
			-I$(srcdir)/../inc \
		    -I$(abs_top_srcdir)/STSW-STM32072/CMSIS/CM3/CoreSupport \
		     -DUSE_STDPERIPH_DRIVER 
			
			