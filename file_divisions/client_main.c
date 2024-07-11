#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 3490
#define SERVER_ADDR "127.0.0.1"
#define MAXDATASIZE 100

int main(){
	int client_fd = create_socket(AF_INET, SOCK_STREAM, 0);

	connect_socket(client_fd, SERVER_ADDR, SERVER_PORT, 4);
	
	printf("Client: connecting to\n");

	char buf[MAXDATASIZE];
	int numbytes;
	if((numbytes = recv(client_fd, buf, MAXDATASIZE - 1, 0)) == -1){
		perror("recv");
		exit(1);
	}

	buf[numbytes] = '\0';
	printf("Client: received '%s'\n", buf);

	char message[1024] = {0};
	printf("Enter msg: ");
	scanf("%s", message);
	write_msg(client_fd, message);
	printf("Message sent to client.\n");

	
	/*	
	int i = 0;
	while(i < 2){
//		char *message = "Hello Server!";
		char message[1024] = {0};
		printf("enter msg: ");
		scanf("%s", message);
		write_msg(client_fd, message);
		printf("Message sent to Client.\n");
		
		char buffer[1024] = {0};
		read_msg(client_fd, buffer, sizeof(buffer));
		printf("Message received from Server is: %s\n", buffer);
		++i;
	}
	*/
	

	close(client_fd);

	return 0;

}
