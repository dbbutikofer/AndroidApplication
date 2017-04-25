#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class Server
{
	SOCKET mySoc;
	SOCKET Listener;

	fd_set Master; //Master file descriptor list
	fd_set read_fds; //Temp file descriptor list

	struct Message_Mask
	{
		uint16_t Msg_Length;
		uint8_t Msg_Type;
		uint8_t Msg_Issued_id;
		char* Msg_data = nullptr;

		~Message_Mask()
		{
			delete[] Msg_data;
		}
	};

	public:
		Server();
		~Server(void);
		//Establishes a listening socket
		bool init(uint16_t port);
		//Recieves data from clients, parses it, responds accordingly
		bool run(void);
		//Notfies clients of close & closes down sockets, Can be called on multiple threads
		bool stop(void);
};

