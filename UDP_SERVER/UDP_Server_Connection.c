#include <stdio.h>      // Default System Calls
#include <stdlib.h>     // Needed for OS X
#include <string.h>     // Needed for Strlen
#include <sys/socket.h> // Needed for socket creating and binding
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define EXPR_SIZE   1024
#define BUFLEN      512
#define TRUE        1
#define SERVERLEN   1024

int main( void )
{
    int fd; // open the file stream as what the udp connect reads as
    int s; // initialize socket int
    struct linger so_linger; // initialize our server linger listening time variable
    so_linger.l_linger = 10000; //sets time in seconds

    setsockopt(s, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);


    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { //AF_INET initialize net protocal type, Sock_DGRAM is what sends packets of info / its partner is SOCK_STREAM
        perror( "socket failed" );
        return 1;
    }

    struct sockaddr_in serveraddr; 					// initialize the pointer for the socket address name
    memset( &serveraddr, 0, sizeof(serveraddr) );	// addresses the server space, telling memset the size also
    serveraddr.sin_family = AF_INET;     //designates the address format that goes with the Internet namespace. this is passed to sin.family, the address family or format of the socket address
    serveraddr.sin_port = htons( 50037 );  // port number. htons converts to server readable info  
    serveraddr.sin_addr.s_addr = htonl( INADDR_ANY ); //"any incoming address" binding to an address

    if ( bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
        perror( "bind failed" );  //server bind test
        return 1;
    }

    char buffer[200];  // make an artibratry buffer size to recieves connection success from client
    for ( int i = 0; i < 1; i++ ) { 
        int length = recvfrom( fd, buffer, sizeof(buffer) - 1, 0, NULL, 0 ); //initialize int length which receives from our file stream, buffer holds the message, at the size of the incoming message
        if ( length < 0 ) { 
            perror( "recvfrom failed" ); // connection recieve error test
            break;
        }
        buffer[length] = '\0'; //puts buffer = to Null in a character context?
        printf( "%d bytes: '%s'\n", length, buffer ); // prints our buffer string from length int
    }

    close( fd );
}