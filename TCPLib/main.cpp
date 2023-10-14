#include<stdio.h>
#include<iostream>
#include"tcplib.h"


int main()
{
	std::cout << "Hello World!" << std::endl;
	TCPListener server = TCPListener();
	if (server.StartListening() != SOCKET_ERROR)
	{
		std::cout << "Server started" << std::endl;
		SOCKET client = server.acceptClient();
		if (client == INVALID_SOCKET)
		{
			std::cout << "Failed to accept client" << WSAGetLastError() << std::endl;
		}
		else
		{
			std::cout << "Client accepted" << std::endl;
			char buffer[1024];
			int result = recv(client, buffer, sizeof(buffer), 0);
			if (result == SOCKET_ERROR)
			{
				std::cout << "Failed to receive data" << WSAGetLastError() << std::endl;
			}
			else
			{
				std::cout << "Received data: " << buffer << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Server failed to start" << WSAGetLastError() << std::endl;
	}
	return 0;
}