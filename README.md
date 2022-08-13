# myLittleEchoServer

클라이언트가 송신한 것을 수신해 그대로 되돌려 송신해주는 서버.
메아리는 소리친대로 돌아온다.

Webserv 과제 구현 전 socket과 관련된 다음 함수들을 사용해보는 것이 목표이다.

```
int socket (int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
```
