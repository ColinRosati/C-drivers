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
     char string[BUFFERSIZE];
     int i = 0;



     printf("Do You want to change IP address? Y or N: \n");
     scanf("%c", &answer);

 	if(answer == 'y'|| answer == 'Y'){
   		 printf("New IP \n");
      
   		 for(;;++i)
		    {
		        string[i] = getchar();
		        if (i > 0 && string[i] == '\n' && string[i] == '\n') break;                
		    }

		    string[i] = 0;


	 //    while( fgets(buffer, BUFFERSIZE , stdin) )// break with ^D or ^Z 
		// {
			
		// 	printf("%s\n", buffer);

		// }
	    
    } else {
	    printf("%s\n", server);
	    printf("Didnt want to change ");
	}

	printf("now your using %s", string);


	return 0;

}