NAME =	exp_sys
FLAGS = -Wall -Werror -Wextra -std=c++11
SRC = main.cpp reader.cpp
CC = g++
OSRC =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OSRC)
		$(CC) -o $(NAME) $(FLAGS) $(OSRC)

%.o: %.cpp
		$(CC) $(FLAGS) -c -o $@ $<

clean:
		rm -f *.o

fclean: clean
		rm -f $(NAME)

re: fclean all