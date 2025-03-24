##
## EPITECH PROJECT, 2024
## Jetpack
## File description:
## Makefile
##

SERVER_DIR	=	server/
CLIENT_DIR	=	client/

SRC_DIR	=	src/

SRC_SERVER	=	$(SERVER_DIR)$(SRC_DIR)main.c	\

SRC_CLIENT	=	$(CLIENT_DIR)$(SRC_DIR)main.cpp	\

NAME_SERVER	=	jetpack_server

NAME_CLIENT	=	jetpack_client

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)
OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

%.o: %.c
	gcc $(CFLAGS_SERVER) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS_CLIENT) -c $< -o $@

CFLAGS_SERVER += -I./$(SERVER_DIR)include/ -Werror -Wall -Wextra -g
CFLAGS_CLIENT += -I./$(CLIENT_DIR)include/ -Werror -Wall -Wextra -g

all:	server client

server:	$(OBJ_SERVER)
	gcc -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS_SERVER)	\

client:	$(OBJ_CLIENT)
	g++ -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS_CLIENT)	\

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov

fclean: clean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_TEST)

re:	fclean all

NAME_TEST	=	unit_tests

SRC_TESTS	=	tests/test.cpp	\

FLAGS_TEST	=	-lcriterion --coverage

CFLAGS_TEST	=	-I./$(SERVER_DIR)include/	\
				-I./$(CLIENT_DIR)include/	\
				-Werror -Wall -Wextra -g

unit_tests: re
	g++ -o $(NAME_TEST) $(SRC_TESTS) $(CFLAGS_TEST) $(FLAGS_TEST)

tests_run: unit_tests
	./$(NAME_TEST)

coverage: unit_tests
	./$(NAME_TEST)
	gcovr --exclude tests/
	gcovr --exclude tests/ --txt-metric branch
	rm $(NAME_TEST)

