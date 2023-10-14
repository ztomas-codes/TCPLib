#pragma once
#include<stdio.h>
#include<iostream>


class TCPClient
{
private:
	std::string m_ip;
public:
	TCPClient(std::string ip)
	{
		m_ip = ip;
		std::cout << "TCPClient created with ip: " << m_ip << std::endl;
	}
};