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

void sendAndReceive(int sock, ssize_t len);

int main(int argc, char **argv)
{
	SOCKETDISCRIPTOR sock;
	struct sockaddr_in serv_addr = {0};
	ssize_t len;

	if(argc != 3) {
		std::cerr << "Usage : " << argv[0] << " <IP> <port>" << std::endl;
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handler("socket() error");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(strtol(argv[2], nullptr, 10));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handler("connect() error");

	sendAndReceive(sock, len);

	close(sock);
	return 0;
}

void sendAndReceive(int sock, ssize_t len)
{
	char message[BUFSIZE];

	while(1) {
		std::cout << "전송할 메시지를 입력하세요(q to quit) : ";
		std::cin >> message;

		if(!strcmp(message, "q"))
			break;
		write(sock, message, strlen(message));

		len = read(sock, message, BUFSIZE - 1);
		message[len] = 0;
		std::cout << "서버로부터 전송된 메시지: " << message << std::endl;
	}
}

void error_handler(const std::string& message)
{
	std::cerr << message << std::endl;
	exit(1);
}

