#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 

int main(void ){
	int fd;
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket failed");
        return 1;
    }
}