motionSystem
============

A domotic motion detector based on MCU Stm32, Raspberry Pi and web server

configue project to build STM32 CortexM3 application
====================================================

LDFLAGS="-Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end" ../configure --host=arm-none-eabi --target=i686-pc-linux-gnu --build=i686-pc-linux-gnu --prefix=<somewhere> CFLAGS="-mthumb -mcpu=cortex-m3"


configue project to build Raspberry Pi Application
==================================================
../configure --host=arm-linux-gnueabihf --target=i686-pc-linux-gnu --build=i686-pc-linux-gnu --prefix=<somewhere> CXXFLAGS="-g -O3"

