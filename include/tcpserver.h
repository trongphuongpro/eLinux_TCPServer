/**
 * @file tcpserver.h
 * @brief Wrapper class for Server-side of TCP/IPv4 socket connection.
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2020 Jan 28
 */


#ifndef __TCPSERVER__
#define __TCPSERVER__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include <vector>
#include "connectionhandler.h"


/**
 * @brief namespace eLinux
 */
namespace eLinux {

/**
 * @brief Class TCPserver used for creating TCP Server/
 */
class TCPServer {
public:

	/**
	 * @brief Constructor.
	 * @param port server's port.
	 */
	TCPServer(int port);


	/**
	 * @brief Destructor.
	 */
	~TCPServer();


	/**
	 * @brief Wait for new connection.
	 * @return -1:failed.
	 */
	virtual int listen();


	/**
	 * @brief Close server.
	 */
	virtual void close();


	/**
	 * @brief Destroy a connection to a client.
	 * @param connection pointer to a ConnectionHandler instance.
	 */
	virtual void destroyHandler(ConnectionHandler* connection);

private:
	int open();

	int port;
	int socketfd;
	bool isConnected;
	std::vector<ConnectionHandler*> connections;
};

} /* namespace eLinux */

#endif /* __TCPSERVER__ */