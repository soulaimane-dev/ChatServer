#include "header.hpp"
#include <unistd.h>


int	main()
{
	int	serverFD = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(8080);
	address.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverFD, (struct sockaddr *)& address, sizeof(address)) < 0)
	{
		std::cerr << "error: in binding" << std::endl;
		close(serverFD);
		return 1;
	}

	if (listen(serverFD, 5) < 0)
	{
		std::cerr << "error: in listing" << std::endl;
		close(serverFD);
		return 1;
	}
	while (true) {
		int clinetFD = accept(serverFD, nullptr, nullptr);
		char buffer[1024] = {0};
		recv(clinetFD, buffer, sizeof(buffer), 0);
		std::cout << buffer << std::endl;
		usleep(500000);
	}
	close(serverFD);
}
