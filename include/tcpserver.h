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

namespace eLinux {

class TCPServer {
public:
	TCPServer(int port);
	~TCPServer();

	virtual int send(std::string message);
	virtual int listen();
	virtual int receive(std::string& message, uint16_t len=1024);

private:
	int port;
	int socketfd;
	int clientSocketfd;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	bool isConnected;
};

} /* namespace eLinux */

#endif /* __TCPSERVER__ */