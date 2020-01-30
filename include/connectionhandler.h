/**
 * @file connectionhandler.h
 * @brief 
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 30
 */


#ifndef __CONNECTIONHANDLER__
#define __CONNECTIONHANDLER__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

namespace eLinux {

class TCPServer;

class ConnectionHandler {
public:
	ConnectionHandler(TCPServer* parent, sockaddr_in* client, int clientSocketfd);
	virtual ~ConnectionHandler();

	virtual int start();
	virtual void wait();
	virtual void stop();

	virtual int send(std::string message);
	virtual int receive(std::string& message, uint16_t len=1024);

protected:
	virtual void threadLoop();

private:
	sockaddr_in *client;
	int clientSocketfd;
	pthread_t thread;
	TCPServer *parent;
	bool isRunning;

	static void *threadHelper(void *hander);
};

} /* namespace eLinux */

#endif /* __CONNECTIONHANDLER__ */