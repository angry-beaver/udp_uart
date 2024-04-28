#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "include/server.h"

int main() {
	const int SIZE = 1024;
	const auto PORT = "54000";
	UDPServer server;

	const int server_error = server.init(PORT);
	if (server_error != 0) {
		std::cout << "Failed create udp server " << std::endl;
		exit(1);
	}
	std::cout << "UDP server is listening on port " << PORT << std::endl;

	while(true)
	{
		char message[SIZE] {};
		int bytes_received = server.receive(message, SIZE);

		if ( bytes_received == -1) {
			std::cout << "Could not receive the message from the client!" << std::endl;
			exit(1);
		}

		std::cout << "Received from client: " << message << std::endl;

		char answer[SIZE] {};
		strcpy(answer, "Server > ");
		strcat(answer, message);

		int bytes_sent = server.send(answer, SIZE);
		if ( bytes_sent == -1) {
			std::cout << "Could not send the answer to the client!" << std::endl;
			exit(1);
		}
	}

}