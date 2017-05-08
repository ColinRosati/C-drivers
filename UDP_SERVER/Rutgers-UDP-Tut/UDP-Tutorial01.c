#include <sys/socket.h>
/* creating our socket */

int main(void ){
	int fd; //socket name
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { //AF_NET is the Address, SOCK_DGRAM is what type of data we are streaming
        perror("socket failed");
        return 1;
    }
}