#include<stdio.h>
#include<iostream>
#include"tcplib.h"


int main()
{
	std::cout << "Hello World!" << std::endl;
	TCPClient client("172.0.0.1");
	return 0;
}