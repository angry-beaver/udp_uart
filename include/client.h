#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

class UDPClient {
public:
    /*
    * Clears memory and closes the socket.
    */    
    ~UDPClient();
    /**
    * @param server_port e.g. 54000
    * @param server_ip_address e.g 127.0.0.1, 192.168.50.150
    * @returns 0 on success or -1 if an error occurs;
    */
    int init(const char *server_port, const char *server_ip_address);
    /**
    *
    * @param message Points to a buffer containing the message to be sent.
    * @param length Specifies the size of the message in bytes.
    * @returns the number of bytes sent on success or -1 if an error occurred.
    */
    int send(const void *message, size_t length);
    /**
    * Sends the message to the client;
    *
    * @param buffer Points to the buffer where the message should be stored.
    * @param length Specifies the length in bytes of the buffer pointed to by the buffer argument.
    * @return the number of bytes received on success or -1 if an error occurred.
    * */
    int receive(void *buffer, size_t length);
private:
	struct addrinfo	*server;
	int sock_d;
};