/*
** EPITECH PROJECT, 2025
** $
** File description:
** client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <poll.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <cstring>
    #include <iostream>
    #include <string>

class ClientHandler {
    public:
        ClientHandler();
        ClientHandler(const char *ip, const char *port);
        ~ClientHandler();

        std::string getMsg();
        void sendMsg(const std::string &msg);

    private:
        void setNonBlocking(int sockfd);

        int _sockfd;
        struct sockaddr_in _serverAddr;
        int _flags;

};

#endif /* !CLIENT_HPP_ */