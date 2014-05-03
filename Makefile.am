OPTIONS=foreign

SUBDIRS=
if MAKE_MCU
SUBDIRS+=motion_detector_mcu
endif

if MAKE_RPI
SUBDIRS+=motion_gateway_rpi
endif

if MAKE_CGI
SUBDIRS+=cgi_application
endif

if MAKE_SERVER
SUBDIRS+=motion_server
endif