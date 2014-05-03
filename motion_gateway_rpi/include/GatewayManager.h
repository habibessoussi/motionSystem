/*
 * GatewayManager.h
 *
 *  Created on: 3 mai 2014
 *      Author: essoussi
 */

#ifndef GATEWAYMANAGER_H_
#define GATEWAYMANAGER_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

class GatewayManager_c
{
public:

	/**
	 * Get the instance
	 * @return the singleton instance
	 */
	static GatewayManager_c& getInstance()
	{
		static GatewayManager_c instance;
		return instance;
	}

	/**
	 * Init the TCP connection
	 * @return Error code
	 */
	uint32_t init_connection();

	/**
	 * Write to server
	 * @param buffer
	 * @return the number written
	 */
	size_t write_server(const uint8_t *buffer);

	/**
	 * Read from server
	 * @param buffer the buffer read
	 * @return number read
	 */
	size_t read_server(uint8_t *buffer);

	/**
	 * Destructor
	 */
	virtual ~GatewayManager_c();


private:

	/**
	 * Server TCP host name
	 */
	static const std::string m_hostname;

	/**
	 * Application port
	 */
	static const uint16_t m_port;

	/**
	 * The client socket
	 */
	int32_t m_clientSocket;

	/**
	 * Constructor
	 * @param hostname Server TCP hostname
	 * @param port TCP port of the web server application (cgi)
	 */
	GatewayManager_c();

};

#endif /* GATEWAYMANAGER_H_ */
