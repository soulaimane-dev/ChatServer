/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:57:18 by sbouabid          #+#    #+#             */
/*   Updated: 2024/10/24 10:14:44 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <exception>
#include <poll.h>
#include <vector>

class	Server
{
	private:
		int	ServerSocketFD;
		std::vector<int> ClientsFds;
		struct	pollfd	fds[1024];

		int		AcceptNewClient();
		void	CheckMovementFromClient();
		void	BroadcastMessage(int fd, char *buffer);

	public:
		void	StartServerSetup();
		void	AcceptConnections();
};

#endif
