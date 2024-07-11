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

void sigchld_handler(int s){
	int saved_errno = errno;

	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}

int main(){
	int sock_fd = create_socket(AF_INET, SOCK_STREAM, 0);
	
	bind_socket(sock_fd, SERVER_PORT, 4, SERVER_ADDRESS);

	listen_socket(sock_fd, 4);
	
	printf("Server: Listening on Port %d\n", SERVER_PORT);

//	printf("Server: Waiting for connections...\n");

	struct sigaction sa;
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &sa, NULL) == -1){
		perror("sigaction");
		exit(1);
	}

	printf("Server: Waiting for connections...\n");

	struct sockaddr_in their_addr;
	socklen_t sin_size;
	int new_fd;
	while(1){
		sin_size = sizeof(their_addr);
		new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &sin_size);
		if(new_fd == -1){
			perror("accept");
			continue;
		}

		char cli_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(their_addr.sin_addr), cli_ip, INET_ADDRSTRLEN);

		printf("Server: got connection from %s\n", cli_ip);

		if(!fork()){
			close(sock_fd);
			if(send(new_fd, "Hello, world!", 13, 0) == -1){
				perror("send");
			}

			char buffer[1024] = {0};
			read_msg(new_fd, buffer, sizeof(buffer));
			printf("Received Message from client: %s\n", buffer);

			close(new_fd);
			exit(0);
		}

		
		close(new_fd);	
	}

	/*
	int i = 0;

	while(i < 4){
		int client_fd = accept_connection(sock_fd, 4);

		handle_client(client_fd);
		++i;
	}
	*/


	/*

	int client_fd =	accept_connection(sock_fd, 4); 

	char buffer[1024] = {0};
	read_msg(client_fd, buffer, sizeof(buffer));
	printf("Received Message from client: %s\n", buffer);

	char *message = "Hello Client!";
	write_msg(client_fd, message);
	printf("Message sent to client.");

	close(client_fd);
	*/
//	close(sock_fd);

	return 0;
}
