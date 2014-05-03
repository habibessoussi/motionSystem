/*
 * motion_gateway_rpi.cpp
 *
 *  Created on: 3 mai 2014
 *      Author: essoussi
 */


#include "GatewayManager.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

int main (int argc, char* argv[])
{

	uint32_t ErrorGateWayCode = 0;

	/** Instanciate the gateway manager */
	GatewayManager_c gatewayManager = GatewayManager_c::getInstance();

	/** Connect to web server */
	ErrorGateWayCode = gatewayManager.init_connection();
	if (ErrorGateWayCode !=  0 )
	{
		std::cerr << "[ERROR]" << strerror(ErrorGateWayCode) << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "[INFO] connected to server " << std::endl;
	}

	/** @TODO : add here the read from UART and write on socket */
	gatewayManager.write_server((const uint8_t*)"\nHey salut\n\n");

	return 0;
}

