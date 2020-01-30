/**
 * @file tcpserver.cpp
 * @brief 
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 28
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "tcpserver.h"


using namespace std;

namespace eLinux {

TCPServer::TCPServer(int port) {
	this->socketfd = -1;
	this->port = port;
	this->isConnected = false;
	this->connections = vector<ConnectionHandler*>();

	assert(open() == 0);
}


TCPServer::~TCPServer() {
	close();
}


int TCPServer::open() {
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0) {
		perror("TCPServer: error opening socket");
		return -1;
	}

	memset(&this->server, 0, sizeof(this->server));
	this->server.sin_family = AF_INET;
	this->server.sin_addr.s_addr = INADDR_ANY;
	this->server.sin_port = htons(this->port);

	if (bind(this->socketfd, (struct sockaddr*)&this->server,
							sizeof(this->server)) < 0) {
		perror("TCPServer: error on binding the socket");
		return -1;
	}

	::listen(this->socketfd, 255);

	return 0;
}


void TCPServer::close() {
	::close(this->socketfd);
}


int TCPServer::listen() {
	while (1) {
		struct sockaddr_in *tempClient = new struct sockaddr_in;
		socklen_t clientLength = sizeof(struct sockaddr_in);

		int tempClientSocketfd = accept(this->socketfd,
									(struct sockaddr*)tempClient,
									&clientLength);

		if (tempClientSocketfd < 0) {
			perror("TCPServer: Failed to bind the client socket properly");
			return -1;
		}
		else {
			ConnectionHandler *conn = new ConnectionHandler(this, 
															tempClient, 
															tempClientSocketfd);
			this->connections.push_back(conn);
			conn->start();
		}
	}
	return 0;
}


void TCPServer::notifyHandlerExit(ConnectionHandler* connection) {
	vector<ConnectionHandler*>::iterator it;

	for (it = this->connections.begin(); it != this->connections.end(); it++) {
		if (*it == connection) {
			this->connections.erase(it);
			printf("TCPServer: Found and deleted the connection reference.\n");
			break;
		}
	}
	delete connection;
}

} /* namespace eLinux */