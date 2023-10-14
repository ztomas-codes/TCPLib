#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>

const int PROTOCOL_TCP = 0;
const int PROTOCOL_UDP = 1;

class SocketFactory
{
	protected:
		std::string Ip;
		UINT16 Port;

		SOCKET _socket;
		WSADATA _wsaData;
		sockaddr_in _socketAdrr;

		int LoadDLL()
		{
			int result = WSAStartup(MAKEWORD(2, 2), &_wsaData);
			return result;
		}
		int CreateSocket(int protocol)
		{
			if (protocol == PROTOCOL_TCP) _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			else if (protocol == PROTOCOL_UDP) _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			else std::cout << "Invalid protocol" << std::endl;
			return _socket;
		}


		void CreateSocketAddress()
		{
			_socketAdrr.sin_family = AF_INET;
			
			PCWSTR ip = (PCWSTR)Ip.c_str();

			InetPton(AF_INET, ip, &_socketAdrr.sin_addr.s_addr);
			_socketAdrr.sin_port = htons(Port);

		}
};

class TCPClient : private SocketFactory
{
	private:
		int Protocol;
	public:
		TCPClient(std::string Ip, UINT16 port, int protocol = PROTOCOL_TCP)
		{
			Ip = Ip;
			Port = port;
			Protocol = protocol;
		}
		int Connect()
		{
			if (LoadDLL() != 0) {
				std::cout << "Failed to load DLL" << std::endl;
				return 1;
			}

			if (CreateSocket(Protocol) == INVALID_SOCKET)
			{
				std::cout << "Failed to create socket" << std::endl;
				WSACleanup();
				return 1;
			}

			CreateSocketAddress();

			return connect(_socket, (SOCKADDR*)&_socketAdrr, sizeof(_socketAdrr));
		}
	
	
};


class TCPListener : private SocketFactory
{
private:
	UINT16 Port;
	int Protocol;
	std::string Ip;

	int BindSocket()
	{


		return bind(_socket, (SOCKADDR*)&_socketAdrr, sizeof(_socketAdrr));
	}

public:
	TCPListener(UINT16 port, int protocol = PROTOCOL_TCP)
	{
		Ip = "172.0.0.1";
		Port = port;
		Protocol = protocol;
	}
	int StartListening()
	{
		if (LoadDLL() != 0) {
			std::cout << "Failed to load DLL" << std::endl;
			return 1;
		}

		if (CreateSocket(Protocol) == INVALID_SOCKET)
		{
			std::cout << "Failed to create socket" << std::endl;
			WSACleanup();
			return 1;
		}

		CreateSocketAddress();

		if (BindSocket() == SOCKET_ERROR)
		{
			std::cout << "Failed to bind socket: " << WSAGetLastError() << std::endl;
			closesocket(_socket);
			WSACleanup();
			return 1;
		}

		return listen(_socket, 2);
	}
	SOCKET acceptClient()
	{
		return accept(_socket, NULL, NULL);
	}
};