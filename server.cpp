//
// Created by Han Gyul Kim on 2022/08/13.
//

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

#define BUFSIZE 1024

typedef int SOCKETDISCRIPTOR;

void error_handler(const std::string& message);

int main(int argc, char **argv)
{
	SOCKETDISCRIPTOR serverSocket;
	SOCKETDISCRIPTOR clientSocket;
	char message[BUFSIZE];
	ssize_t len = 0;

	struct sockaddr_in serverAddress = {0};
	struct sockaddr_in clientAddress = {0};
	socklen_t clientAddressSize;

	if(argc != 2) {
		std::cerr << "Usage : " << argv[0] << " <port>" << std::endl;
		exit(1);
	}

	std::cout << "socket()" << std::endl;
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(serverSocket == -1)
		error_handler("socket() error");
	std::cout << "socket() done" << std::endl;

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(strtol(argv[1], nullptr, 10));


	std::cout << "bind()" << std::endl;
	if(bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress) ) == -1)
		error_handler("bind() error");
	std::cout << "bind() done" << std::endl;

	std::cout << "listen()" << std::endl;
	if(listen(serverSocket, 5) == -1)
		error_handler("listen() error");
	std::cout << "listen() done" << std::endl;

	clientAddressSize = sizeof(clientAddress);

	std::cout << "accept()" << std::endl;
	clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
	if(clientSocket == -1)
		error_handler("accept() error");
	std::cout << "accept() done" << std::endl;

	std::cout << "len: " << len << std::endl;
	while((len = read(clientSocket, message, BUFSIZE)) != 0) {
		std::cout << "len: " << len << std::endl;
		write(1, "received: ", 10);
		write(clientSocket, message, len);
		write(1, message, len);
		write(1, "\nread not zero\n", 15);
	}
	write(1, "read zero\n", 10);
	close(clientSocket);

	return 0;
}

void error_handler(const std::string& message)
{
	std::cerr << message << std::endl;
	exit(1);
}