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
#include "tcpserver.h"


using namespace std;

namespace eLinux {

TCPServer::TCPServer(int port) {
	this->socketfd = -1;
	this->clientSocketfd = -1;
	this->port = port;
	this->isConnected = false;
}


TCPServer::~TCPServer() {
	close(this->socketfd);
	close(this->clientSocketfd);
}


int TCPServer::listen() {
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0) {
		perror("TCPServer: error opening socket");
		return -1;
	}

	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = INADDR_ANY;
	this->serverAddress.sin_port = htons(this->port);

	if (bind(this->socketfd, (struct sockaddr*)&this->serverAddress,
							sizeof(this->serverAddress)) < 0) {
		perror("TCPServer: error on binding the socket");
		return -1;
	}

	::listen(this->socketfd, 5);

	socklen_t clientLength = sizeof(this->clientAddress);
	this->clientSocketfd = accept(this->socketfd,
								(struct sockaddr*)&this->clientAddress,
								&clientLength);

	if (this->clientSocketfd < 0) {
		perror("TCPServer: Failed to bind the client socket properly");
		return -1;
	}

	return 0;
}


int TCPServer::send(string message) {
	const char* buffer = message.c_str();

	int n = write(this->clientSocketfd, buffer, message.length());
	if (n < 0) {
		perror("TCPServer: error writing to server socket");
		return -1;
	}
	return 0;
}


int TCPServer::receive(string& message, uint16_t len) {
	char buffer[len];
	int n = read(this->clientSocketfd, buffer, len);

	if (n < 0) {
		perror("TCPServer: error reading from server socket");
		return -1;
	}

	message = string(buffer);
	return 0;
}

}