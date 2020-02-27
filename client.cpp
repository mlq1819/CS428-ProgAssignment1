// UDP Client

// Must have the UDP Pinger Server running before you can run this client

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 12000
#define ATTEMPTS 10

int main() { 
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 
	
	// Fill client information 
	cliaddr.sin_family = AF_INET; // IPv4 
	cliaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	cliaddr.sin_port = htons(PORT); // port number
	
	// Bind the socket with the client address 
	bind(sockfd, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));
	
	// random generator
	srand(time(0));
	
	/*struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(rcv_sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
		perror("Error");
	}*/
	time_t time_s, time_r;
	
	for(int i=0; i<ATTEMPTS; i++){
		//The client sends a message to the server?
		time(&time_s);
		sendto(sockfd, (const char *)buffer, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
			
		//Receive the server ping along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		time(&time_r);
		buffer[n] = '\0';
	}
	return 0;
}