#include <stdio.h>
#include <unistd.h>
#include "tcpserver.h"


using namespace std;
using namespace eLinux;


void respond(void *arg) {
	printf("conn: %p\n", arg);
	ConnectionHandler* conn = static_cast<ConnectionHandler*>(arg);
	
	string msg;
	int ret;

	while (conn->isRunning()) {
		msg = "Welcome to BBB server";
		ret = conn->send(msg);
		
		if ((ret = conn->receive(msg)) > 0) {
			printf("[Receive] %s\n", msg.c_str());
		}
		else {
			break;
		}

		//conn->stop();
	}

	conn->getParent()->destroyHandler(conn);
}


int main() {
	puts("BBB TCP Socket Server");

	string msg;
	TCPServer server(1234);

	server.listen(respond);

	puts("stop");
}