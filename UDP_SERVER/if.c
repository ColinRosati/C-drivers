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
#define BUFFERSIZE 40

int main( void )
{
     char *server = "127.0.0.1";
     char answer;
     char  *myserver = calloc(1,1), buffer[BUFFERSIZE];


     printf("Do You want to change IP address? Y or N: \n");
     scanf("%c", &answer);

 if(answer == 'y'|| answer == 'Y'){
        printf("New IP");
	     	
	     	while( fgets(buffer, BUFFERSIZE , stdin) )/* break with ^D or ^Z */
			{
				myserver = realloc( myserver, strlen(myserver)+1+strlen(buffer) );
			  strcat( myserver, buffer ); /* note a '\n' is appended here everytime */
			  printf("%s\n", buffer);
			}
	    
    } else {
	    printf("%s\n", server);
	    printf("Didnt want to change ");
	}

	printf("now your using %s", myserver);


	return 0;

}