#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

#define PORT 8000

void ErrorHandling(char *message);

int main()
{
	WSADATA		wsaData;
	SOCKET		servSocket, clntSocket;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[] = "Hello World";

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	servSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (servSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(PORT);

	if (bind(servSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(servSocket, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	clntSocket = accept(servSocket, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (clntSocket == INVALID_SOCKET)
		ErrorHandling("accept() error");

	send(clntSocket, message, sizeof(message), 0);
	closesocket(servSocket);
	closesocket(clntSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}