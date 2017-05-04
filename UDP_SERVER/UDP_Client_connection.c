#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // this is my socket library look here for documentation
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define EXPR_SIZE   1024
#define BUFLEN      512
#define TRUE        1
#define FALSE       0
#define SERVERLEN   1024

#define PROMPT "You are now connected to this server" // this is our message to send. defining this varible here is good becuase we can get the sizeof


int main( void )
{
    int fd; //initialize filestream. UDP is interpreted as a file stream
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {  ////AF_INET designates address format for net, Sock_DGRAM is what sends packets of info / its partner is SOCK_STREAM
        perror("socket failed"); //test connection fail
        return 1;
    }


    struct sockaddr_in serveraddr; // initialize the pointer for the socket address name
    memset( &serveraddr, 0, sizeof(serveraddr) ); // addresses the server space, telling memset the size also
    serveraddr.sin_family = AF_INET;  //designates the address format that goes with the Internet namespace. this is passed to sin.family, the address family or format of the socket address
    serveraddr.sin_port = htons( 50037 );              // port number     htons converts to server readable info       
    serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  //server address. htonl convert values for the sin_port member.

    for ( int i = 0; i < 4; i++ ) {
        if (sendto( fd, PROMPT, sizeof(PROMPT), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) { //sends our prompt and checks if addresses are connected in this if statement, weird. 
            perror( "sendto failed" );  // sendto test
            break;
        }
        printf( "message sent\n" ); // tells us that the message was sent and did its client task
    }

    close(fd);
}