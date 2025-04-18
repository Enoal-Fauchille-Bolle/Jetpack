#include "ClientHandler.hpp"

#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>

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
    // Create a blocking TCP socket
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Prepare server address
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(std::stoi(port));
    if (inet_pton(AF_INET, ip, &_serverAddr.sin_addr) <= 0) {
        perror("inet_pton");
        close(_sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect (blocking)
    if (connect(_sockfd, reinterpret_cast<struct sockaddr *>(&_serverAddr),
                sizeof(_serverAddr)) == -1) {
        perror("connect");
        close(_sockfd);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Destroy the ClientHandler object.
 *
 * This function closes the socket when the client object is destroyed.
 */
ClientHandler::~ClientHandler()
{
    if (_sockfd != -1) {
        close(_sockfd);
    }
}

/**
 * @brief Get a message from the server.
 *
 * This function retrieves a message from the server using poll to check for
 * incoming data, then reads using read().
 *
 * @return The message received from the server
 */
std::string ClientHandler::getMsg()
{
    struct pollfd fds;
    fds.fd = _sockfd;
    fds.events = POLLIN;
    fds.revents = 0;

    // Poll with zero timeout for non-blocking check
    int ret = poll(&fds, 1, 0);
    std::string message;

    if (ret > 0 && (fds.revents & POLLIN)) {
        char buffer[1024];
        std::memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(_sockfd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            message.assign(buffer, static_cast<size_t>(bytesRead));
            std::cout << message << std::endl;
        }
    }
    return message;
}

/**
 * @brief Send a message to the server.
 *
 * This function sends a message to the server using write().
 *
 * @param msg The message to send
 */
void ClientHandler::sendMsg(const std::string &msg)
{
    const char *data = msg.c_str();
    size_t total = 0;
    size_t toSend = msg.length();

    while (total < toSend) {
        ssize_t sent = write(_sockfd, data + total, toSend - total);
        if (sent < 0) {
            perror("write");
            break;
        }
        total += static_cast<size_t>(sent);
    }
}
