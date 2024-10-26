#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <poll.h>
#include <iostream>
#include <unistd.h>
#include <exception>
#include <cstring>
#include <netinet/in.h>
#include <vector>

class	Server
{
	private:
		int	ServerFD;
		std::vector<int> ClientFDs;
		std::vector<pollfd> pfds;
		char buffer[1024];

		int		AcceptNewClient();
		void	MonitorClientMovements();

	public:
		Server();
		void	AcceptConnections();
};




#endif
