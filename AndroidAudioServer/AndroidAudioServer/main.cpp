#include "Server.h"
#include <iostream>

Server server;
bool isRunning = true;

int main(void)
{
	WSADATA wsaData;

	int IResult;

	//Initialize Winsock
	IResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (IResult != 0)
	{
		printf("WSAStartup failed: %d\n", IResult);
		return 1;
	}

	IResult = server.init(atoi(DEFAULT_PORT));
	
		while (isRunning)
		{
			isRunning = server.run();
		}

	IResult = server.stop();

	return 0;
}