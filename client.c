////By Malik Hassan Raza (208046) Muhammad Nouman Tahir (218663) BSCS 7B
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 1024 
#define PORT 8080 
#define SA struct sockaddr 
void client(int sockfd) 
{ 
	char buff[MAX]; 
	//// sending command to the server
	bzero(buff, sizeof(buff)); 
	printf("Enter the command :\n"); 
	gets(buff);
	

	write(sockfd, buff, sizeof(buff)); 
	
	/// reading result from the server and writing it in file
	bzero(buff, sizeof(buff)); 
	read(sockfd, buff, sizeof(buff)); 
	printf("From Server : %s", buff);
	FILE *fp = fopen("rec_file.txt", "wb");
	fwrite(buff, 1, sizeof(buff), fp);
}

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Socket creation failed\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("Connection with the server failed.\n"); 
		exit(0); 
	} 
	else
		printf("Connected to the server.\n"); 


	client(sockfd); 
	close(sockfd); 
} 

