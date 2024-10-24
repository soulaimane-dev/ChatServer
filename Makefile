CC = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = server
SRCF = main.cpp Server.cpp
RM = rm -f
OBJF = $(SRCF:.cpp=.o)
HEADERS = Server.hpp

all: $(NAME)

%.o: %.cpp $(HEADERS)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJF)
	$(CC) $(CPPFLAGS) $(OBJF) -o $(NAME)

clean:
	$(RM) $(OBJF)

fclean: clean
	$(RM) $(NAME)
