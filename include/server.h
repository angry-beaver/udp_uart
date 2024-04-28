#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

class UDPServer {
public:
    /**
     * Constructor
    */
    UDPServer();
    /*
    * Clears memory and closes the socket.
    */    
    ~UDPServer();
    /**
    * @param server_port e.g. 54000
    * @returns 0 on success or -1 if an error occurs;
    */
    int init(const char *server_port);
    /**
    * Sends the message to the client;
    *
    * @param buffer Points to the buffer where the message should be stored.
    * @param length Specifies the length in bytes of the buffer pointed to by the buffer argument.
    * @return the number of bytes received on success or -1 if an error occurred.
    * */
    int receive(void *buffer, size_t length);
    /**
    *
    * @param message Points to a buffer containing the message to be sent.
    * @param length Specifies the size of the message in bytes.
    * @returns the number of bytes sent on success or -1 if an error occurred.
    */
    int send(const void *message, size_t length);
private:
    struct addrinfo *server;
	int sock_d;
	struct sockaddr client;
    socklen_t client_size;
};