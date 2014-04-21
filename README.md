motionSystem
============

A domotic motion detector based on MCU Stm32, Raspberry Pi and web server

configue
========

LDFLAGS="-Wl,--start-group -lgcc -lc -lm -lrdimon -Wl,--end" ../configure --host=arm-none-eabi --target=i686-pc-linux-gnu --build=i686-pc-linux-gnu --prefix=/home/essoussi/workspace/motionSystem CFLAGS="-mthumb -mcpu=cortex-m3"
