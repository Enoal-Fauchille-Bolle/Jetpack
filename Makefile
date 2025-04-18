##
## EPITECH PROJECT, 2025
## Jetpack
## File description:
## Makefile
##

# Compiler and flags
CC		  = gcc
CXX		 = g++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 -g
LDFLAGS	 = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SERVER_DIR  = server
CLIENT_DIR  = client
SRC_DIR	 = src
INCLUDE_DIR = include
ELEMENT_DIR = elements

# Source files for server
SRC_SERVER  =   $(SERVER_DIR)/$(SRC_DIR)/main.c			  \
				$(SERVER_DIR)/$(SRC_DIR)/get_server_options.c  \
				$(SERVER_DIR)/$(SRC_DIR)/map_parser.c		  \
				$(SERVER_DIR)/$(SRC_DIR)/connection.c		  \
				$(SERVER_DIR)/$(SRC_DIR)/client_handler.c	  \
				$(SERVER_DIR)/$(SRC_DIR)/socket.c			  \
				$(SERVER_DIR)/$(SRC_DIR)/game.c				\
				$(SERVER_DIR)/$(SRC_DIR)/collisions.c				\
				$(SERVER_DIR)/$(SRC_DIR)/command_parser.c	  \
				$(SERVER_DIR)/$(SRC_DIR)/command_executor.c	\
				$(SERVER_DIR)/$(SRC_DIR)/handshake_response_executor.c  \
				$(SERVER_DIR)/$(SRC_DIR)/utils.c			   \
				$(SERVER_DIR)/$(SRC_DIR)/destroyers.c		  \
				$(SERVER_DIR)/$(SRC_DIR)/client_commands/quit.c		\
				$(SERVER_DIR)/$(SRC_DIR)/client_commands/ready.c	   \
				$(SERVER_DIR)/$(SRC_DIR)/client_commands/fly.c		 \
				$(SERVER_DIR)/$(SRC_DIR)/server_commands/start.c	   \
				$(SERVER_DIR)/$(SRC_DIR)/server_commands/player.c	  \
				$(SERVER_DIR)/$(SRC_DIR)/server_commands/end.c		 \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/id.c	  \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/map.c	 \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/start.c

# Source files for client
SRCS_CLIENT =   $(CLIENT_DIR)/$(SRC_DIR)/main.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/ClientHandler.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/Game.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/GameManager.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Coin.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Lazer.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Map.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Player.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/PlayerList.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/View.cpp

# Executable names
NAME_SERVER = jetpack_server
NAME_CLIENT = jetpack_client

# Object files
OBJ_SERVER  = $(SRC_SERVER:.c=.o)
OBJ_CLIENT  = $(SRCS_CLIENT:.cpp=.o)

# Additional flags (placed before pattern rules)
CFLAGS_SERVER += -I./$(SERVER_DIR)/include/ -Werror -Wall -Wextra -g
CFLAGS_CLIENT += -I./$(CLIENT_DIR)/include/ -Werror -Wall -Wextra -g

# Pattern rule for C files
%.o: %.c
	$(CC) $(CFLAGS_SERVER) -c $< -o $@

# Pattern rule for C++ files
%.o: %.cpp
	$(CXX) $(CFLAGS_CLIENT) -c $< -o $@

# Default target
all: server client

server: $(OBJ_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJ_SERVER) $(CFLAGS_SERVER) -lm

client: $(OBJ_CLIENT)
	$(CXX) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(CFLAGS_CLIENT) $(LDFLAGS)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
