#include <stdio.h>
#include "tcpserver.h"


using namespace std;
using namespace eLinux;

int main() {
	puts("BBB TCP Server");

	string msg;
	TCPServer server(1234);

	do {
		server.listen();
		
		server.receive(msg);
		printf("[Receive] %s\n", msg.c_str());

		msg = "Welcome to BBB server";
		server.send(msg);
	} while (1);
}