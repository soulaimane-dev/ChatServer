
Server = Server.cpp
Clinet = Clinet.cpp
all:
	c++ Server.cpp -o server
	c++ Clinet.cpp -o clinet
clean:
	rm server clinet
