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
    struct sockaddr_in serveraddr, remaddr;
    int fd, slen=sizeof(remaddr);
    char *server = "127.0.0.1";  //Local Machine or other machine
    char *newIP;
    char answer;
    char msganswer; 
    char buf[BUFLEN];
    char buffer[100];// pass the new ip address from stdin and store it in buffer
    char line[20];
    char line2[20];
    char *message = "hello";
    char *my_message;
    char string2[BUFFERSIZE];
    char string[BUFFERSIZE];
    char ipstring[BUFFERSIZE];

    int i = 0;
    

    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket failed");
        return 1;
    }

    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);              
    serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  
    if (inet_aton(server, &remaddr.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
    } 
    


    printf("Do you want to send a message? Y or N: \n");
    
    fgets(line, sizeof(line),stdin);
    sscanf(line, "%30[^\n]\n", &msganswer);
    if(msganswer == 'y'|| msganswer == 'Y'){          
        printf("Your Message: ");

         for(;;++i)
            {
                string[i] = getchar();
                if (i > 0 && string[i] == '\n' && string[i] == '\n') break;                
            }

            string[i] = 0;


        // while(fgets(buffer, sizeof buffer, stdin))/* break with ^D or ^Z. buffer holds our new IP */
        // {
        //     scanf("%30[^\n]", buffer);
        //     size_t len = strlen(buffer);
        //     if (len > 0 && buffer[len-1] == '\n') {
        //       buffer[--len] = '\0';
        //     }
        // }

        my_message = string; 
        printf("%s\n", my_message);

    } else {
        my_message = message;
    }
          

    printf("Do You want to change IP address? Y or N: \n");


    fgets(line2, sizeof(line2),stdin);
    sscanf(line2, "%30[^\n]", &answer);
    if(answer == 'y'|| answer == 'Y'){
        printf("New IP: \n");

        for(;;++i)
            {
                ipstring[i] = getchar();
                if (i > 0 && ipstring[i] == '\n' && ipstring[i] == '\n') break;                
            }

            ipstring[i] = 0;

        newIP = ipstring; 
        printf("%s\n", ipstring);

        
        
        memset((char *) &remaddr, 0, sizeof(remaddr));
        remaddr.sin_family = AF_INET;
        remaddr.sin_port = htons(PORT);
        if (inet_aton(newIP, &remaddr.sin_addr)==0) { // initializing IP with new address
            fprintf(stderr, "inet_aton() failed\n");
    
         } 


            if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&remaddr, slen)==-1) {
                perror("sendto");
            }
        
           printf("message: %s sent on IP %s", my_message, newIP);
        
    }
     else {


        for ( int i = 0; i < 1; i++ ) {
            if (sendto( fd, my_message, strlen(my_message), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
            perror( "sendto failed" );
            break;
            }
           printf( "message sent on local server\n" );
        }
    }  
    

    printf("%c\n", answer);

    close(fd);
}