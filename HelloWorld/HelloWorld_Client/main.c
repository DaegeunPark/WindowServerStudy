#include <stdio.h>
#include <stdlib.h>
#include <WS2tcpip.h>
#include <WinSock2.h>

#define IP "127.0.0.1"
#define PORT 8000

void ErrorHandling(char *message);

int main()
{
	WSADATA  wsaData;
	SOCKET   hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("hSocketet() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8000);
	inet_pton(AF_INET, IP, &servAddr.sin_addr);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");

	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		ErrorHandling("read() error!");

	printf("Message From Server : %s \n", message);

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}