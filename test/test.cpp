#include <stdio.h>
#include <unistd.h>
#include "tcpserver.h"


using namespace std;
using namespace eLinux;

int main() {
	puts("BBB TCP Server");

	string msg;
	TCPServer server(1234);

	server.listen();
}