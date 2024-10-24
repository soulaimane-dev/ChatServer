#include "Server.hpp"
#include <exception>
#include <iostream>

int	main()
{
	try {
		Server serv;
		serv.StartServerSetup();
		serv.AcceptConnections();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
