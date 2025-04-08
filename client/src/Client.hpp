/*
** EPITECH PROJECT, 2025
** $
** File description:
** client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <string>
    #include <sys/socket.h>
    #include <arpa/inet.h>

    class Client {
        public:
            Client() = default;
            Client(const Client&) = default;
            Client& operator=(const Client&) = default;
            Client(Client&&) = default;
            Client(const char *ip,const char *port);
            ~Client();
            std::string get_msg();
            void send_msg(const std::string& msg);

        protected:
        private:
            int sockfd;

            struct sockaddr_in serverAddr;

            void setNonBlocking(int sockfd);

            int flags;
    };

#endif /* !CLIENT_HPP_ */