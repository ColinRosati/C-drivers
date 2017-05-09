/*
        demo-udp-03: udp-send: a simple udp client
	send udp messages
	This sends a sequence of messages (the # of messages is defined in MSGS)
	The messages are sent to a port defined in SERVICE_PORT 

        usage:  udp-send

        Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <fcntl.h> // for open
#include <unistd.h> // for close


#define PORT 21234

#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */


int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	char buf[BUFLEN];	/* message buffer */
	int recvlen;		/* # bytes in acknowledgement message */
	char *server = "127.0.0.1";	/* change this to use a different server */
	//char *my_message = "hello, this is a test message";
	char *my_message;
	char str1[20];


	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		//exit(1);
	}

	//make my message
		printf("Your Message: ");
		scanf("%50[^\n]", str1); // scanf terminates at the first new line
		my_message = str1;

	
	/* now let's send the messages */

	// for (i=0; i < MSGS; i++) { //this loops through multiple packets printing the same messgae
	// 	printf("Sending packet %d to %s port %d\n", i, server, PORT);
	// 	sprintf(buf, "This is packet %d", i);
	// 	if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&remaddr, slen)==-1) {
	// 		perror("sendto");
	// 		//return 0;
	// 		//exit(1);
	// 	} 

		while (1) {
		printf("Sending packet %d to %s port %d\n", i, server, PORT);
		sprintf(buf, "This is packet %d", i);
		if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&remaddr, slen)==-1) {
			perror("sendto");
			//return 0;
			//exit(1);
		}

		/* now receive an acknowledgement from the server */
		recvlen = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
                if (recvlen >= 0) {
                        buf[recvlen] = 0;	/* expect a printable string - terminate it */
                        printf("received message: \"%s\"\n", buf);
                        return 0;
                }
	}

	// close(fd);
	// return 0;
}
