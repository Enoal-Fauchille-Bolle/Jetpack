/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Destroyers Header
*/

#ifndef DESTROYERS_H_
    #define DESTROYERS_H_

    #include <poll.h>

    #include "commands.h"
    #include "server.h"

void destroy_client(client_t *, bool verbose);
void destroy_command(command_t *command);
void destroy_server(server_t *server, struct pollfd *fds, client_t *clients);

#endif /* !DESTROYERS_H_ */
