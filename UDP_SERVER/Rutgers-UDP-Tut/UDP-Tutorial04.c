#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <string.h> //for memcpy
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <stdlib.h>
#include <netdb.h> // needed for call gethostbyname
#include <arpa/inet.h>

#define PORT 5555

int main(int argc, char *argv[]){

	int i;
	int fd; // socet name
	struct hostent *hp; // host info
	struct in_addr **addr_list;
	char host;                                         ///bug is the host
	struct sockaddr_in servaddr; // serve address
	char *my_message = "this is a test message";

	/* fill in the server's address and data */
	memset((char*)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	inet_pton(AF_INET, "127.0.0.1", &addr_list);
	host = gethostbyaddr(&addr_list, sizeof addr_list, AF_INET);

	 if (argc != 2) {
        fprintf(stderr,"usage: ghbn hostname\n");
        return 1;
    }

    if ((hp = gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        return 2;
    }

     printf("Official name is: %s\n", hp->h_name);
    printf("    IP addresses: ");
    addr_list = (struct in_addr **)hp->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");

	/* look up the address of the server given its name */
	 hp = gethostbyname(host);                                  ///bug is the host
	 if (!hp) {
	 	fprintf(stderr, "could not obtain address of %s\n", host);
	 	return 0;
	 }

	/* put the host's address into the server address structure */
	//memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

	/* send a message to the server */
	if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("sendto failed");
		return 0;
	}

}