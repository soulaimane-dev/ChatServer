#include "Server.hpp"

int	main()
{
	try {
		Server serv;
		serv.AcceptConnections();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
