#include "server.h"

UDPServer::UDPServer() {
    client_size = sizeof(struct sockaddr);
}

UDPServer::~UDPServer() {
    freeaddrinfo(server);
	close(sock_d);
}

int UDPServer::init(const char *server_port) {
    struct addrinfo hints;

    /* configure the remote address */
    memset(&hints, 0, sizeof(hints));   /* clear memory */
    hints.ai_family = AF_INET;			/* IPv4 connection */
    hints.ai_socktype = SOCK_DGRAM;		/* UDP, datagram */
    hints.ai_flags = AI_PASSIVE;		/* accept any connection */
    int error = getaddrinfo(0, server_port, &hints, &server);
    if (error != 0) {
        std::cout << "Failed to get the address info" << std::endl;
        return - 1;
    }

    /* create the socket */
    sock_d = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if( sock_d == -1 )
    {
        std::cout << "Failed to create the socket" << std::endl;
        
        return -1;
    }

    /* bind the server to a socket */
    int bind_error = bind(sock_d, server->ai_addr, server->ai_addrlen);
    if (bind_error == -1) {
        std::cout << "Failed to bind the socket" << std::endl;
        
        return -1;
    }

    return 0;   
}

int UDPServer::receive(void *buffer, size_t length) {
    return recvfrom(sock_d, buffer, length, 0, &client, &client_size);
}

int UDPServer::send(const void *message, size_t length) {
    return sendto(sock_d, message, length, 0, &client, client_size);
}