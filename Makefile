##
## EPITECH PROJECT, 2025
## Jetpack
## File description:
## Makefile
##

# Compiler and flags
CXX			= g++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++17 -g
LDFLAGS		= -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SERVER_DIR	= server
CLIENT_DIR	= client
SRC_DIR		= src
INCLUDE_DIR	= include
ELEMENT_DIR	= elements

# Server source files
SRCS_SERVER	=	$(SERVER_DIR)/$(SRC_DIR)/main.c \
				$(SERVER_DIR)/$(SRC_DIR)/get_server_options.c \
				$(SERVER_DIR)/$(SRC_DIR)/map_parser.c \
				$(SERVER_DIR)/$(SRC_DIR)/connection.c \
				$(SERVER_DIR)/$(SRC_DIR)/client_handler.c \
				$(SERVER_DIR)/$(SRC_DIR)/socket.c \
				$(SERVER_DIR)/$(SRC_DIR)/command_parser.c \
				$(SERVER_DIR)/$(SRC_DIR)/command_executor.c \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_response_executor.c \
				$(SERVER_DIR)/$(SRC_DIR)/utils.c \
				$(SERVER_DIR)/$(SRC_DIR)/destroyers.c \
				$(SERVER_DIR)/$(SRC_DIR)/commands/quit.c \
				$(SERVER_DIR)/$(SRC_DIR)/commands/ready.c \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/id.c \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/map.c \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/lobby.c \
				$(SERVER_DIR)/$(SRC_DIR)/handshake_responses/start.c

# Client source files
SRCS_CLIENT	=	$(CLIENT_DIR)/$(SRC_DIR)/main.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/ClientHandler.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/Game.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/GameManager.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Coin.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Lazer.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Map.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/Player.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/PlayerList.cpp \
				$(CLIENT_DIR)/$(SRC_DIR)/$(ELEMENT_DIR)/View.cpp

# Object files
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT	= $(SRCS_CLIENT:.cpp=.o)

# Executable names
NAME_SERVER	= jetpack_server
NAME_CLIENT	= jetpack_client

# Default target
all: $(NAME_SERVER) $(NAME_CLIENT)

# Server build
$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) -o $@ $^ $(CFLAGS)

# Client build
$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

# Clean object files
clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

# Remove executables
fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
