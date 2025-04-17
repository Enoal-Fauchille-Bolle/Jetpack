##
## EPITECH PROJECT, 2024
## Jetpack
## File description:
## Makefile
##

SERVER_DIR	=	server/
CLIENT_DIR	=	client/
CLIENT_ELEMENT_DIR	=	elements/

SRC_DIR	=	src/

SRC_SERVER	=	$(SERVER_DIR)$(SRC_DIR)main.c	\
				$(SERVER_DIR)$(SRC_DIR)get_server_options.c	\
				$(SERVER_DIR)$(SRC_DIR)map_parser.c	\
				$(SERVER_DIR)$(SRC_DIR)connection.c	\
				$(SERVER_DIR)$(SRC_DIR)client_handler.c	\
				$(SERVER_DIR)$(SRC_DIR)socket.c	\
				$(SERVER_DIR)$(SRC_DIR)command_parser.c	\
				$(SERVER_DIR)$(SRC_DIR)command_executor.c	\
				$(SERVER_DIR)$(SRC_DIR)handshake_response_executor.c	\
				$(SERVER_DIR)$(SRC_DIR)utils.c	\
				$(SERVER_DIR)$(SRC_DIR)destroyers.c	\
				$(SERVER_DIR)$(SRC_DIR)commands/quit.c	\
				$(SERVER_DIR)$(SRC_DIR)commands/ready.c	\
				$(SERVER_DIR)$(SRC_DIR)handshake_responses/id.c	\
				$(SERVER_DIR)$(SRC_DIR)handshake_responses/map.c	\
				$(SERVER_DIR)$(SRC_DIR)handshake_responses/lobby.c	\
				$(SERVER_DIR)$(SRC_DIR)handshake_responses/start.c	\

SRC_CLIENT	=	$(CLIENT_DIR)$(SRC_DIR)main.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)Client.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)Game.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)GameManager.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)$(CLIENT_ELEMENT_DIR)Coin.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)$(CLIENT_ELEMENT_DIR)Map.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)$(CLIENT_ELEMENT_DIR)Player.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)$(CLIENT_ELEMENT_DIR)PlayerList.cpp	\
				$(CLIENT_DIR)$(SRC_DIR)$(CLIENT_ELEMENT_DIR)View.cpp	\

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
		-lsfml-graphics -lsfml-window -lsfml-system

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
