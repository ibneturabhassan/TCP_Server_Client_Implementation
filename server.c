////By Malik Hassan Raza (208046) Muhammad Nouman Tahir (218663) BSCS 7B

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 1024 
#define PORT 8080 
#define SA struct sockaddr 


void serv(int sockfd) 
{ 
	char buff[MAX];
	bzero(buff, MAX); 
	
	// read command from client and copy it in buffer 
	read(sockfd, buff, sizeof(buff)); 
	
	strcat(buff, ">dump.txt");
	///running command	
	system(buff);
	//// done creating file

	//// setting buffer to null reading file and sending it over to client
	bzero(buff, MAX);

	FILE *fp = fopen("dump.txt", "rb");
	printf("sending results\n");
	fread(buff, 1, sizeof(buff), fp);
	// and send that buffer to client 
	write(sockfd, buff, sizeof(buff)); 
	printf("results sent\n");

} 

int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// careting socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding created socket to given IP & verify 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket binding failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket binded successfully\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listening failed\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("Server could not accept client\n"); 
		exit(0); 
	} 
	else
		printf("Server acccepted the client\n"); 


	serv(connfd); 
	close(sockfd); 
} 

