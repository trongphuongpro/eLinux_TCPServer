/**
 * @file tcpserver.h
 * @brief 
 * @author Nguyen Trong Phuong
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

namespace eLinux {

class TCPServer {
public:
	TCPServer(int port);
	~TCPServer();

	virtual int listen();
	virtual void close();
	virtual void notifyHandlerExit(ConnectionHandler* connection);

private:
	int open();

	int port;
	int socketfd;
	struct sockaddr_in server;
	bool isConnected;
	std::vector<ConnectionHandler*> connections;
};

} /* namespace eLinux */

#endif /* __TCPSERVER__ */