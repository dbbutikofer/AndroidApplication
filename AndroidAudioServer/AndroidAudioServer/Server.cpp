#include "Server.h"



Server::Server()
{
}


Server::~Server()
{
}

bool Server::init(uint16_t port)
{
	mySoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create a socket.

	FD_ZERO(&Master);
	FD_ZERO(&read_fds);

	sockaddr_in Server_Soc;
	Server_Soc.sin_port = htons(port);
	Server_Soc.sin_addr.S_un.S_addr = INADDR_ANY;

	if (mySoc < 0)
	{
		return false;
	}

	if (bind(mySoc, (sockaddr*)&Server_Soc, sizeof(Server_Soc)) < 0) //Bind the socket.
	{
		closesocket(mySoc);
		return false;
	}

	if (listen(mySoc, 10) == -1) //Listen on the socket for a client.
	{
		return false;
	}

	FD_SET(mySoc, &Master);
	return true;
}

bool Server::run(void)
{
	FD_ZERO(&read_fds);

	read_fds = Master;


	if (FD_ISSET(mySoc, &read_fds))  //Accept a connection from a client.
	{
		sockaddr_in Server_Soc;
		Server_Soc.sin_addr.S_un.S_addr = INADDR_ANY;
		int size = sizeof(Server_Soc);
		Listener = accept(mySoc, (sockaddr*)&Server_Soc, &size);
		FD_SET(Listener, &Master);
	}


	//Receive and send data.


	return true;
}

bool Server::stop(void)
{
	//Disconnect.
	int shutmySoc = shutdown(mySoc, SD_BOTH);
	int shutListener = shutdown(Listener, SD_BOTH);

	int closemySoc = closesocket(mySoc);
	int closeListener = closesocket(Listener);

	return false;
}
