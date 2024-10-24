/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:57:25 by sbouabid          #+#    #+#             */
/*   Updated: 2024/10/24 09:49:12 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "server.hpp"
#include <__nullptr>
#include <cstring>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/_endian.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

void	Server::StartServerSetup()
{
	ServerSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in	ServerAddress;

	if (ServerSocketFD == -1 )
		throw std::runtime_error("Socket Creation Failed !");

	ServerAddress.sin_addr.s_addr = INADDR_ANY;
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(6667);

	if (bind(ServerSocketFD, (struct sockaddr *)& ServerAddress, sizeof(ServerAddress)) == -1)
	{
		close(ServerSocketFD);
		throw std::runtime_error("Bind Fail !");
	}

	if (listen(ServerSocketFD, 64) == -1)
	{
		close(ServerSocketFD);
		throw std::runtime_error("Listen Fail !");
	}

	std::cout << "IP : 127.0.0.1" << std::endl;
	std::cout << "PORT : 6667" << std::endl;
}

void	Server::AcceptConnections()
{
	fds[0].fd = ServerSocketFD;
	fds[0].events = POLLIN;

	while (true)
	{
		int num_ready = poll(fds, ClientsFds.size() + 1, -1);

		if (num_ready == -1) {
			throw std::runtime_error("Poll failed");
		}

		if ((fds[0].events & POLLIN) && AcceptNewClient() == -1)
			continue ;
		CheckMovementFromClient();
	}
}

int	Server::AcceptNewClient()
{
	int newClient = accept(ServerSocketFD, nullptr, nullptr);
	if (newClient == -1)
		return -1;
	std::cout << "New Client Connect Welcome :)\n";
	ClientsFds.push_back(newClient);
	fds[ClientsFds.size()].fd = newClient;
	fds[ClientsFds.size()].events = POLLIN;
	return 0;
}

void	Server::CheckMovementFromClient()
{
	char	buffer[1024];

	for (int i = 1; i < ClientsFds.size(); i++)
	{
		if (fds[i].revents & POLLIN)
		{
			memset(buffer, 0, 1024);
			int bytes = recv(fds[i].fd, buffer, 1024, 0);
			if (bytes == 0)
			{
				ClientsFds.erase(ClientsFds.begin() + i - 1);
				std::cout << "Client Desconected \n";
			}
			// else if
		}
	}
}
