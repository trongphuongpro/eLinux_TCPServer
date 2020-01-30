/**
 * @file connectionhandler.cpp
 * @brief Handler for multithreaded connection.
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2020 Jan 30
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include "tcpserver.h"
#include "connectionhandler.h"

using namespace std;

namespace eLinux {

ConnectionHandler::ConnectionHandler(TCPServer* parent,
									sockaddr_in *client,
									int clientSocketfd,
									CallbackType callback): parent{parent}
{
	this->client = client;
	this->clientSocketfd = clientSocketfd;
	this->__isRunning = false;
	this->callback = callback;
}


ConnectionHandler::~ConnectionHandler() {
	delete this->client;
}


int ConnectionHandler::start() {
	this->__isRunning = true;
	if (pthread_create(&this->thread, NULL, threadHelper, this) != 0) {
		perror("ConnectionHandler: cannot create new thread.");
		return -1;
	}
	return 0;
}


void ConnectionHandler::stop() {
	this->__isRunning = false;
}


void ConnectionHandler::wait() {
	pthread_join(this->thread, NULL);
}


int ConnectionHandler::send(string message) {
	const char* buffer = message.c_str();

	int n = write(this->clientSocketfd, buffer, message.length());
	if (n < 0) {
		perror("ConnectionHandler: error writing to server socket");
		return -1;
	}
	return n;
}


int ConnectionHandler::receive(string& message, uint16_t len) {
	char buffer[len];
	int n = read(this->clientSocketfd, buffer, len);

	if (n < 0) {
		perror("ConnectionHandler: error reading from server socket");
		return -1;
	}

	message = string(buffer);
	return n;
}


void* ConnectionHandler::threadHelper(void* handler) {
	((ConnectionHandler*)handler)->callback(handler);
	return 0;
}


bool ConnectionHandler::isRunning() {
	return this->__isRunning;
}


TCPServer* ConnectionHandler::getParent() {
	return this->parent;
}

} /* namespace eLinux */