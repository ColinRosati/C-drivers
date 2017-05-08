#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // sockets
#include <netinet/in.h> // Needed to use struct sockaddr_in


/* Naming our socket
binding an address to the socket. This involves requesting an address from the DNS

 transport address is defined in a socket address structure.
 */

int main(void ){
	int fd; // socket name
	struct sockaddr_in myaddr; //socket address arbitrary on client side

/* bind to an arbitrary return address */
/* because this is the client side, we don't care about the address */
/* since no application will initiate communication here - it will */
/* just send responses */
/* INADDR_ANY is the IP address and 0 is the socket */
/* htonl converts a long integer (e.g. address) to a network representation */
/* htons converts a short integer (e.g. port) to a network representation */

    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { //AF_NET is the Address, SOCK_DGRAM is what type of data we are streaming
        perror("socket failed");
        return 1;
    }

    memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET; // The address family we used when we set up the socket. In our case, it's AF_INET.
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY); //You local machine's IP
	myaddr.sin_port = htons(0); //The port number (the transport address). You can explicitly assign a transport address (port) or allow the operating system to assign one. 
								// htons convert four-byte and two-byte numbers into network representations.
								// host to network - short : convert a number into a 16-bit network representation. This is commonly used to store a port number into a sockaddr structure.

    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
	perror("bind failed");
	return 0;
}

}