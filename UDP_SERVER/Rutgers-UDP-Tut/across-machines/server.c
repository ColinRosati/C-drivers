#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h> // for close

#define BUFSIZE 2048

int main()
{
    int cont,create_socket,new_socket,addrlen,fd;
    unsigned char buf[BUFSIZE];
    int bufsize = 1024; 
    unsigned int nameLen=0;
    unsigned int client_address_size=0;
    char *buffer = malloc(10);
    char fname[256];
    struct sockaddr_in address,client;
    int recvlen;
    int msgcnt = 0;			/* count # of messages we received */

    if ((create_socket = socket(AF_INET,SOCK_DGRAM,0)) > 0)
    printf("The socket was created\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons(38970);

    if (bind(create_socket,(struct sockaddr *)&address,sizeof(address))== 0)
        printf("Binding Socket\n");

    nameLen=sizeof(address);

    if (getsockname(create_socket,(struct sockaddr *)&address,&nameLen)<0)
    {
        printf("\n\ngetsockname() error\n");
        exit(3);
    }

    printf("Port assigned is %d\n", ntohs(address.sin_port));

    client_address_size=sizeof(client);



    if(recvfrom(create_socket,fname, 255,0,(struct sockaddr *) &client,&client_address_size)<0)
    {
        printf("\n\nrecvfrom() failed\n");
        exit(4);
    }

   for (;;) {
		printf("waiting on port %d\n", 15000);
		recvlen = recvfrom(create_socket, buf, BUFSIZE, 0, (struct sockaddr *)&address, &nameLen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\" (%d bytes)\n", buf, recvlen);
		}
		else
			printf("uh oh - something went wrong!\n");
		sprintf(buffer, "call number %d", msgcnt++);
		printf("sending response \"%s\"\n", buf);
		}

    sendto(create_socket,"*",1,0,(struct sockaddr *) &client,client_address_size);

    printf("Request Completed\n");
    return close(create_socket);
}