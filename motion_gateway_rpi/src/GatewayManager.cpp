/*
 * GatewayManager.cpp
 *
 *  Created on: 3 mai 2014
 *      Author: essoussi
 */

#include "GatewayManager.h"

#include <errno.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>

/* Initialize static members */
const std::string GatewayManager_c::m_hostname = "192.168.1.14";
const uint16_t GatewayManager_c::m_port = 0xA380;

GatewayManager_c::GatewayManager_c():m_clientSocket(0)
{

}

uint32_t GatewayManager_c::init_connection()
{
	m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sin = 	{ 0 };

	if (m_clientSocket == -1)
	{
		return (errno);
	}

	sin.sin_addr.s_addr = inet_addr(m_hostname.c_str());
	sin.sin_port = htons(m_port);
	sin.sin_family = AF_INET;

	if (connect(m_clientSocket, (sockaddr *) &sin, sizeof(sockaddr)) == -1)
	{
		return (errno);
	}

	return 0; /* Success */
}

size_t GatewayManager_c::write_server(const uint8_t *buffer)
{
	return send(m_clientSocket, buffer, sizeof(buffer), 0);
}

size_t GatewayManager_c::read_server(uint8_t *buffer)
{
	return recv(m_clientSocket, buffer, 1024 - 1, 0);
}

