#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> 
#include <string.h> //for memcpy
#include <netinet/in.h> // Needed to use struct sockaddr_in
#include <stdlib.h>
#include <netdb.h> // needed for call gethostbyname

#define PORT 5555
#define BUFSIZE 2048

int main(void){

	int fd; // our socket
	struct sockaddr_in myaddr; // serve address
	struct sockaddr_in remaddr; //remote address
	socklen_t addrlen = sizeof(remaddr); //length of address
	int recvlen;		// # bytes recieved
	unsigned char buf[BUFSIZE]; // recieve buffer

	//creat UDP socket
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("cannot create socket\n");
		return 0;
	}


	//bind the socket to any valid IP address and a specific port
	memset((char*)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;

	}

	//loop thourgh recieving data and printing it
	for (;;) {
		printf("waiting on port %d\n", PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("recieved message: \"%s\"\n", buf);
		}
	}
	//dont ext with return or close (fd)
	

}