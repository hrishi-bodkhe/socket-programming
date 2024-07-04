#include "socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int create_socket(int ai_family, int ai_socktype, int ai_protocol){
	int sockfd = socket(ai_family, ai_socktype, ai_protocol);

	if(sockfd < 0){
		perror("Failed to create a socket.");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}

void bind_socket(int sockfd, int port, int ip_version, char *address){
	if(ip_version == 4){
		struct sockaddr_in serv_addr;
		
		memset(&serv_addr, 0, sizeof(serv_addr));
		
		serv_addr.sin_family = AF_INET;
	//	serv_addr.sin_addr.s_addr = inet_addr(address); // Converts IPv4 string to binary format
		serv_addr.sin_port = htons(port);

		// Converts IPv4 address string to binary format
		if(inet_aton(address, &serv_addr.sin_addr) <= 0){
			perror("Invalid address");
			exit(EXIT_FAILURE);
		}

		if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			perror("Bind Failed.");
			exit(EXIT_FAILURE);
		}
	}
	else if(ip_version == 6){
		struct sockaddr_in6 serv_addr;

		memset(&serv_addr, 0, sizeof(serv_addr));

		serv_addr.sin6_family = AF_INET6;
		serv_addr.sin6_port = htons(port);

		// Convert the IPv6 address string to binary format
		if(inet_pton(AF_INET6, address, &serv_addr.sin6_addr) <= 0){
			perror("Invalid address");
			exit(EXIT_FAILURE);
		}

		if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			perror("Bind Failed");
			exit(EXIT_FAILURE);
		}
	}
	else{
		perror("Invalid Version for IP.");
		exit(EXIT_FAILURE);
	}

}

void listen_socket(int sockfd, int backlogs){
	if(listen(sockfd, backlogs) < 0){
		perror("Listen Failed.");
		exit(EXIT_FAILURE);
	}
}

void connect_socket(int sockfd, const char *address, int port, int ip_version){
	if(ip_version == 4){
		struct sockaddr_in serv_addr;
		
		memset(&serv_addr, 0, sizeof(serv_addr));
		
		serv_addr.sin_family = AF_INET;
	//	serv_addr.sin_addr.s_addr = inet_addr(address); // Converts IPv4 string to binary format
		serv_addr.sin_port = htons(port);

		// Converts IPv4 address string to binary format
		if(inet_aton(address, &serv_addr.sin_addr) <= 0){
			perror("Invalid address");
			exit(EXIT_FAILURE);
		}

		if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			perror("Connection Failed.");
			exit(EXIT_FAILURE);
		}
	}
	else if(ip_version == 6){
		struct sockaddr_in6 serv_addr;

		memset(&serv_addr, 0, sizeof(serv_addr));

		serv_addr.sin6_family = AF_INET6;
		serv_addr.sin6_port = htons(port);

		// Convert the IPv6 address string to binary format
		if(inet_pton(AF_INET6, address, &serv_addr.sin6_addr) <= 0){
			perror("Invalid address");
			exit(EXIT_FAILURE);
		}

		if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			perror("Connection Failed");
			exit(EXIT_FAILURE);
		}
	}
	else{
		perror("Invalid Version for IP.");
		exit(EXIT_FAILURE);
	}
}

int accept_connection(int sockfd, int ip_version){
	if(ip_version == 4){
		struct sockaddr_in cli_addr;
		socklen_t cli_len = sizeof(cli_addr);

		int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

		if(newsockfd < 0){
			perror("Accept Failed.");
			exit(EXIT_FAILURE);
		}

		char cli_ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(cli_addr.sin_addr), cli_ip, INET_ADDRSTRLEN);
		printf("Server: got connection from %s\n", cli_ip);

		return newsockfd;
	}
	else if(ip_version == 6){
		struct sockaddr_in6 cli_addr;
		socklen_t cli_len = sizeof(cli_addr);

		int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

		if(newsockfd < 0){
			perror("Accept Failed.");
			exit(EXIT_FAILURE);
		}

		char cli_ip[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &(cli_addr.sin6_addr), cli_ip, INET6_ADDRSTRLEN);
		printf("Server: got connection from %s\n", cli_ip);

		return newsockfd;
	}
	else{
		perror("Invalid Version.");
		exit(EXIT_FAILURE);
	}

	return -1;
}

void write_msg(int sockfd, char *msg){
	if(send(sockfd, msg, strlen(msg), 0) == -1){
		perror("Send Failed.");
		exit(EXIT_FAILURE);
	}
}

void read_msg(int sockfd, char buffer[], size_t buffer_size){
	if(recv(sockfd, buffer, buffer_size, 0) == -1){
	       perror("Receive Failed.");
               exit(EXIT_FAILURE);
	}
}	
