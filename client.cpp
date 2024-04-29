#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "lib/serialib.h"
#include "include/client.h"

int main() {
	const int SIZE = 1024;
	// udp
	const auto PORT = "54000";
	const auto SERVER = "127.0.0.1";
	const auto SERIAL_PORT = "/dev/tty.usbserial-110";
	const int BAUDS = 9600; 
	UDPClient client;

	const int client_error = client.init(PORT, SERVER);
	if (client_error != 0) {
		perror("Failed create udp client - ");
		exit(1);
	}
	std::cout << "Client socket created" << std::endl;
	
	serialib serial;

    char serial_error = serial.openDevice(SERIAL_PORT, BAUDS);

	if (serial_error != 1) {
		perror("Failed open serial device - ");
		exit(1);
	}

	std::cout << "Successfully connected to serial device " << SERIAL_PORT << std::endl;


	while(true)
	{
		char message[SIZE] {};
        /* prompt for input */
		std::cout << std::endl << "Waiting for message from " << SERIAL_PORT  << "..." << std::endl;

		while (true) {
			if (serial.available()) {
				// Read the string
            	const int bytes_received = serial.readString(message, '\n', SIZE);

				if (bytes_received < 0) {
					perror("Error while reading - ");
					continue;	
				}
				// remove '\n'
				message[bytes_received - 1] = '\0';
				break;
			}
			usleep(10000);
		}

		std::cout << "Received from " << SERIAL_PORT << ": " << message << std::endl;
		std::cout << std::endl;
		std::cout << "Send the message to the server" << std::endl;
		/* send the string to the server */
		int bytes_sent = client.send(message, strlen(message));
		if ( bytes_sent == -1) {
			perror("Could not send to the server");
			continue;
		}

		char answer[SIZE] {};
		// try to receive some data, this is a blocking call
        int bytes_received = client.receive(answer, SIZE);;
		if ( bytes_received == -1) {
			perror("Could not receive the message from the server - ");
			continue;
		} else {
			std::cout << "Received from server: " << answer << std::endl;
			serial.writeString(answer);		
		}

    }/* end while */

	return(0);
}