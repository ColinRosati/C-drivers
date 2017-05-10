#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <time.h>       // To control the timeout mechanism
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

#define EXPR_SIZE   1024
#define BUFLEN      512
#define TRUE        1
#define FALSE       0
#define SERVERLEN   1024
#define PORT 21234

int main( void )
{
    struct sockaddr_in serveraddr, remaddr;
    int fd, slen=sizeof(remaddr);
    char *server = "127.0.0.1";  //CHANGE THIS ADDRESS TO ANOTHER MACHINE
    //char var;
    // char *answer = &var;
    char answer; 
    char *newIP;
    char buf[BUFLEN];
    char  *myserver = calloc(1,1), buffer[BUFFERSIZE];
    

    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket failed");
        return 1;
    }

    printf("%c\n", answer);

    printf("Do You want to change IP address? Y or N: \n");
    scanf("\n You answer %c", &answer);
    if( answer == 'y' || answer == 'Y'){
        printf("New IP\n");
        while( fgets(buffer, BUFFERSIZE , stdin) )/* break with ^D or ^Z */
            {
                myserver = realloc( myserver, strlen(myserver)+1+strlen(buffer) );
              strcat( myserver, buffer ); /* note a '\n' is appended here everytime */
              printf("%s\n", buffer);
            }
    } 

    printf("%c\n", answer);

    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);              
    serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  


    memset((char *) &remaddr, 0, sizeof(remaddr));
    remaddr.sin_family = AF_INET;
    remaddr.sin_port = htons(PORT);
    if (inet_aton(server, &remaddr.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        //exit(1);
    }

    for ( int i = 0; i < 4; i++ ) {
        if (sendto( fd, "THIS IS A CONNECTION", 5, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
            perror( "sendto failed" );
            break;
        }
        printf( "message sent\n" );
    }

    close(fd);
}