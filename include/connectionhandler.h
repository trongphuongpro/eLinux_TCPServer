/**
 * @file connectionhandler.h
 * @brief Handler for multithreaded connection.
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2020 Jan 30
 */


#ifndef __CONNECTIONHANDLER__
#define __CONNECTIONHANDLER__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

/**
 * @brief namespace eLinux
 */
namespace eLinux {


/**
 * @brief class TCPServer
 *
 * Declaration.
 */
class TCPServer;


/**
 * @brief Class ConnectionHandler is used to handle a connection to server.
 */
class ConnectionHandler {
public:

	/**
	 * @brief Constructor
	 * @param [in] parent pointer to a TCPServer instance.
	 * @param [in] client pointer to struct sockaddr_in contaning IPv4 socket address.
	 * @param [in] clientSocketfd file descriptor to client's socket.
	 */
	ConnectionHandler(TCPServer* parent, sockaddr_in* client, int clientSocketfd);


	/**
	 * @brief Destructor
	 */
	virtual ~ConnectionHandler();


	/**
	 * @brief Start new thread to handle new connection.
	 * @return 0:success,-1:failed.
	 */
	virtual int start();


	/**
	 * @brief Wait until thread terminated.
	 */
	virtual void wait();


	/**
	 * @brief Terminate running thread.
	 */
	virtual void stop();


	/**
	 * @brief Send a message to client.
	 * @param [in] message message will be sent.
	 * @return 0:success,-1:failed.
	 */
	virtual int send(std::string message);


	/**
	 * @brief Receive a message from client.
	 * @param [out] message message will be received.
	 * @param [in] len the max length of received message.
	 * @return 0:success,-1:failed.
	 */
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