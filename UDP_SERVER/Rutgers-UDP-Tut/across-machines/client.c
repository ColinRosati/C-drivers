#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main()
{
    int create_socket,cont,res;
    char *arg="192.168.1.8";

    int bufsize = 1024;
    int server_address_size=0;
    char *buffer = malloc(10);
    char fname[256];
    struct sockaddr_in address;
    int serv_addr_size = sizeof(address);
    char *my_message;
    char str1[30];

    if ((create_socket = socket(AF_INET,SOCK_DGRAM,0)) > 0)
        printf("The Socket was created\n");

    address.sin_family = AF_INET;
    address.sin_port = htons(15000);
    address.sin_addr.s_addr=inet_addr(arg);

    if (connect(create_socket,(struct sockaddr *) &address,sizeof(address)) == 0)
        printf("The connection was accepted with the server %s...\n",arg);
	
    printf("On Port %d\n", address.sin_port);

    // printf("Enter The Filename to Request : ");
    // scanf("%s",fname);
    // res=sendto(create_socket, fname, sizeof(fname), 0,(struct sockaddr *) &address,sizeof(address));
    // if(res<0)
    // {
    //     printf("\n\nSendto falied...\n");
    //     exit(0);
    // }
    // printf("Request Accepted... Receiving File...\n\n");

    // 

    // printf("The contents of file are...\n\n");

    // while((cont=recvfrom(create_socket, buffer, 10, 0,(struct sockaddr *) &address,&serv_addr_size))>0) 
    // {
    //     if(buffer[cont-1]=='*')
    //        break;
    //     write(1, buffer, cont);

    // }

   		server_address_size=sizeof(address);

    	printf("Your Message: ");
		scanf("%50[^\n]", str1); // scanf terminates at the first new line
		my_message = str1;
	
	


    return close(create_socket);
}