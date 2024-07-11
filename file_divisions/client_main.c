#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 3490
#define SERVER_ADDR "127.0.0.1"
//#define SERVER_ADDR "192.168.122.82"
#define MAXDATASIZE 100

int main(){
	int client_fd = create_socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in server_addr;
	socklen_t addr_size;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
//	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	
	if (inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr) <= 0) {
		perror("inet_pton");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	addr_size = sizeof(server_addr);
	
	char buffer[1024] = {0};
	scanf("%s", buffer);
	
	if(sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_size) == -1){
		perror("Send Failed.");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	printf("Message Sent.\n");

	char recv_buff[1024] = {0};
	if(recvfrom(client_fd, recv_buff, sizeof(recv_buff), 0, NULL, NULL) == -1){
		perror("Receive Failed.");
		close(client_fd);
		exit(EXIT_FAILURE);
	}

	printf("Received Message: %s\n", recv_buff);

	close(client_fd);

	return 0;

}
