/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Connection Header
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_

    #include <poll.h>
    #include <stdbool.h>

    #include "client.h"
    #include "server.h"

    #define POLL_TIMEOUT 10000

// Client Handler
void handle_connection(struct pollfd *fd, client_t *client);

// Socket
server_t *setup_socket(int port, bool debug);

// Connection
int process_connections(server_t *server);

#endif /* !CONNECTION_H_ */
