#include "client.h"

UDPClient::~UDPClient() {
    freeaddrinfo(server);
	close(sock_d);
}

int UDPClient::init(const char *server_port, const char *server_ip_address) {
    struct addrinfo hints;

    /* configure the remote address */
    memset(&hints, 0, sizeof(hints));   /* clear memory */
    hints.ai_family = AF_INET;			/* IPv4 */
    hints.ai_socktype = SOCK_DGRAM;		/* UDP connection */
    int error = getaddrinfo(server_ip_address, server_port, &hints, &server);
    if (error != 0) {
        std::cout << "Failed to get the address info" << std::endl;
        return -1;
    }

    /* create the socket */
    sock_d = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if( sock_d == -1 )
    {
        std::cout << "Failed to create the socket" << std::endl;
        
        return -1;
    }

    return 0;
}

int UDPClient::send(const void * message, size_t length) {
    return sendto(sock_d, message, length, 0, server->ai_addr, server->ai_addrlen);
}

int UDPClient::receive(void * buffer, size_t length) {
    return recvfrom(sock_d, buffer, length, 0, server->ai_addr, &server->ai_addrlen);
}