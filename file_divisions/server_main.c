#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SERVER_PORT 3490
#define SERVER_ADDRESS "127.0.0.1"


int main(){
	int sock_fd = create_socket(AF_INET, SOCK_DGRAM, 0);
	
	bind_socket(sock_fd, SERVER_PORT, 4, SERVER_ADDRESS);
	
	printf("UDP Server: Listening on Port %d\n", SERVER_PORT);

//	printf("Server: Waiting for connections...\n");
	

	int i = 0;
	socklen_t addr_size;
	struct sockaddr_in client_addr;

	while(i < 4){
		char buffer[1024] = {0};

		addr_size = sizeof(client_addr);
		if(recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &addr_size) == -1){
			perror("Receive Failed.");
			exit(EXIT_FAILURE);
		}

		printf("Received Message: %s\n", buffer);
		
		char *msg = "Hello, Client!";
		if(sendto(sock_fd, msg, strlen(msg), 0, (struct sockaddr*)&client_addr, addr_size) == -1){
			perror("Send Failed.");
			exit(EXIT_FAILURE);
		}
		++i;
	}

	close(sock_fd);

	return 0;
}
