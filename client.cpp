// UDP Client

// Must have the UDP Pinger Server running before you can run this client

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h>
#include <ctime>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 12000
#define ATTEMPTS 10

int main(int argc, char ** argv) { 
	/*if(argc!=2){
		std::cout << "Usage: " << argv[0] << " xxx.xx.xx.xxx" << std::endl;
		return 1;
	}*/
	
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr; 
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	
	//Fill server information
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	//inet_addr(argv[1]); // kek
	servaddr.sin_port = htons(PORT); // port number
	
	clock_t start, end;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&timeout,sizeof(timeout)) < 0) {
		perror("Error");
	}
	
	
	std::cout << "\nclient> Sending to Port " << servaddr.sin_port << "\n" << std::endl;
	
	for(int i=0; i<ATTEMPTS; i++){
		//The client sends a message to the server?
		start = clock();
		sendto(sockfd, (const char *)buffer, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
			
		//Receive the server ping along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, ( struct sockaddr *) &servaddr, &len);
		end = clock();
		if(n<0){ //timeout
			std::cout << "packet lost..." << std::endl;
			continue;
		}
		buffer[n] = '\0';
		long rtt = (end-start)*1000/CLOCKS_PER_SEC;
		std::cout << rtt << " milliseconds" << std::endl;
	}
	return 0;
}