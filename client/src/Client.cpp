/*
** EPITECH PROJECT, 2025
** $
** File description:
** client
*/

#include "Client.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <poll.h>
#include <fcntl.h>

Client::Client(const char *ip,const char *port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(std::stoi(port));
    inet_pton(AF_INET, ip, &serverAddr.sin_addr);
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    setNonBlocking(sockfd);
}

Client::~Client() {
    close(sockfd);
}

void Client::setNonBlocking(int sockfd) {
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

std::string Client::get_msg() {
    struct pollfd fds;
    fds.fd = sockfd;
    fds.events = POLLIN;
    fds.revents = 0;

    int ret = poll(&fds, 1, 0);

    std::string message;
    if (ret > 0 && (fds.revents & POLLIN)) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0) {
            message = std::string(buffer);
            std::cout << message;
        }
    }
    return message;
}

void Client::send_msg(const std::string& msg) {
    send(sockfd, msg.c_str(), msg.length(), 0);
}
