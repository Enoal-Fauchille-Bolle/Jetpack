/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** client
*/

#include "ClientHandler.hpp"

/**
 * @brief Default constructor for ClientHandler.
 */
ClientHandler::ClientHandler()
{
}

/**
 * @brief Construct a new ClientHandler object and connect to the server.
 *
 * This function initializes the client by creating a socket and connecting to
 * the server.
 *
 * @param ip The IP address of the server
 * @param port The port number of the server
 */
ClientHandler::ClientHandler(const char *ip, const char *port)
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(std::stoi(port));
    inet_pton(AF_INET, ip, &_serverAddr.sin_addr);
    if (connect(_sockfd, (struct sockaddr *)&_serverAddr,
            sizeof(_serverAddr)) == -1) {
        perror("connect");
        close(_sockfd);
        exit(EXIT_FAILURE);
    }
    setNonBlocking(_sockfd);
}

/**
 * @brief Destroy the ClientHandler object.
 *
 * This function closes the socket when the client object is destroyed.
 */
ClientHandler::~ClientHandler()
{
    close(_sockfd);
}

/**
 * @brief Set the socket to non-blocking mode.
 *
 * This function sets the socket to non-blocking mode using fcntl.
 *
 * @param sockfd The socket file descriptor
 */
void ClientHandler::setNonBlocking(int sockfd)
{
    int flags = fcntl(sockfd, F_GETFL, 0);

    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Get a message from the server.
 *
 * This function retrieves a message from the server using poll to check for
 * incoming data.
 *
 * @return The message received from the server
 */
std::string ClientHandler::getMsg()
{
    struct pollfd fds = {.fd = _sockfd, .events = POLLIN, .revents = 0};
    int ret = poll(&fds, 1, 0);

    std::string message;
    if (ret > 0 && (fds.revents & POLLIN)) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(_sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0) {
            message = std::string(buffer);
            std::cout << message;
        }
    }
    return message;
}

/**
 * @brief Send a message to the server.
 *
 * This function sends a message to the server.
 *
 * @param msg The message to send
 */
void ClientHandler::sendMsg(const std::string &msg)
{
    send(_sockfd, msg.c_str(), msg.length(), 0);
}
