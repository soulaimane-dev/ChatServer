#include "header.hpp"
#include <unistd.h>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "error: in args" << std::endl;
		return 1;
	}
	int	clinetFD = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addressServer;
	addressServer.sin_family = AF_INET;
	addressServer.sin_port = htons(8080);
	addressServer.sin_addr.s_addr = INADDR_ANY;

	if (connect(clinetFD, (struct sockaddr *)& addressServer, sizeof(addressServer)) < 0)
	{
		std::cerr << "error: in banding" << std::endl;
		close(clinetFD);
		return 1;
	}
	send(clinetFD, av[1], strlen(av[1]), 0);
	close(clinetFD);

}
