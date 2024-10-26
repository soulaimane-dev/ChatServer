#include "Server.hpp"
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

Server::Server()
{
	ServerFD = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerFD == -1)
		throw std::runtime_error("Socket Creation Failed !");

	struct	sockaddr_in	ServerAddress;
	ServerAddress.sin_port = htons(6667);
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = INADDR_ANY;
	int opt = 1;
	setsockopt(ServerFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(ServerFD, (struct sockaddr *)& ServerAddress, sizeof(ServerAddress)) == -1)
	{
		close(ServerFD);
		throw std::runtime_error("Bind Failed !");
	}

	if (listen(ServerFD, 10) == -1)
	{
		close(ServerFD);
		throw std::runtime_error("Listen Failed !");
	}

	pollfd pfd;
	pfd.events = POLLIN;
	pfd.fd = ServerFD;
	pfds.push_back(pfd);

	std::cout << "The Server has been Started :)" << std::endl;
	std::cout << "IP: 127.0.0.1 \nPORT: 6667" << std::endl;
}

void	Server::AcceptConnections()
{
	while (true) {
		int	pollEnvent = poll(pfds.data(), pfds.size(), -1);
		if (pollEnvent == -1)
			throw std::runtime_error("Poll Failed !");
		if (pfds[0].revents & POLLIN)
		{
			if (AcceptNewClient() == -1)
				continue;
		}
		MonitorClientMovements();
	}
}

int	Server::AcceptNewClient()
{
	int	clientFd = accept(ServerFD,nullptr, nullptr);
	if (clientFd == -1)
		return -1;
	std::cout << "New Clinet Connected !" << std::endl;
	ClientFDs.push_back(clientFd);
	pollfd pfd;
	pfd.fd = clientFd;
	pfd.events = POLLIN;
	pfds.push_back(pfd);
	return 0;
}

void	Server::MonitorClientMovements()
{
	for (size_t i = 1; i < pfds.size(); i++)
	{
		if (pfds[i].revents & POLLIN)
		{
			memset(buffer, 0, sizeof(buffer));
			int bytes = recv(pfds[i].fd, buffer, sizeof(buffer), 0);
			if (bytes <= 0)
			{
				std::cout << "Client Disconnected !" << std::endl;
				close(pfds[i].fd);
				pfds.erase(pfds.begin() + i);
				ClientFDs.erase(ClientFDs.begin() + i - 1);
				i--;
			}
			else {
				std::cout << "New message received\n";
				BroadcastMessage(pfds[i].fd);
			}
		}
	}
}

void	Server::BroadcastMessage(int fd)
{
	std::vector<int>::iterator it;
	for (it = ClientFDs.begin(); it != ClientFDs.end(); it++)
	{
		if (*it == fd)
			continue;
		send(*it, buffer, sizeof(buffer), 0);
	}
}
