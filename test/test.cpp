#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "tcpserver.h"


using namespace std;
using namespace eLinux;


void respond(void *arg) {
	printf("conn: %p\n", arg);
	ConnectionHandler* conn = static_cast<ConnectionHandler*>(arg);
	
	string msg = "OK";
	int ret;

	while (conn->isRunning()) {

		ret = conn->receive(msg);
		printf("recv ret: %d, error: %d\n", ret, errno);

		if (ret > 0) {
			printf("[Receive] %s\n", msg.c_str());
		}
		else {
			printf("Client has disconnected.\n");
			break;
		}

		ret = conn->send(msg);
		printf("send ret: %d, error: %d\n", ret, errno);

		puts("-------------------------------");
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