/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** Socket File
*/

#include <stdlib.h>

#include "connection.h"
#include "server.h"

/**
 * @brief Set the read mode for the server.
 *
 * This function sets the read mode for the server. It is used to
 * prevent the server from blocking on read operations.
 *
 * @param a Boolean value indicating whether to set read mode or not.
 */
static int listen_socket(int server_sockfd)
{
    if (listen(server_sockfd, MAX_CLIENTS) == -1) {
        perror("listen");
        return -1;
    }
    return 0;
}

/**
 * @brief Bind the socket to the specified address.
 *
 * This function binds the socket to the specified address and port.
 *
 * @param server_sockfd The socket file descriptor.
 * @param server_addr The address to bind to.
 * @return int 0 on success, -1 on failure.
 */
static int bind_socket(int server_sockfd, struct sockaddr_in *server_addr)
{
    socklen_t addr_len = sizeof(*server_addr);

    if (bind(server_sockfd, (struct sockaddr *)server_addr, addr_len) == -1) {
        perror("bind");
        return -1;
    }
    return 0;
}

/**
 * @brief Initialize a sockaddr_in structure with the specified port.
 *
 * This function initializes a sockaddr_in structure with the given port
 * and sets the address family to AF_INET (IPv4).
 *
 * @param port The port number to set.
 * @return struct sockaddr_in The initialized sockaddr_in structure.
 */
static struct sockaddr_in init_sockin(int port)
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    return server_addr;
}

/**
 * @brief Set up a socket file descriptor.
 *
 * This function creates a socket file descriptor for the server.
 *
 * @return int The socket file descriptor, or -1 on failure.
 */
static int setup_socket_fd(void)
{
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_sockfd == -1) {
        perror("socket");
    }
    return server_sockfd;
}

/**
 * @brief Set the final port number for the server.
 *
 * This function retrieves the port number assigned to the socket
 * after binding.
 *
 * @param server_sockfd The socket file descriptor.
 * @return int The final port number.
 */
static int set_final_port(int server_sockfd)
{
    struct sockaddr_in server_addr = {0};
    socklen_t addr_len = sizeof(server_addr);

    getsockname(server_sockfd, (struct sockaddr *)&server_addr, &addr_len);
    return ntohs(server_addr.sin_port);
}

/**
 * @brief Initialize the server structure.
 *
 * This function initializes the server structure with the specified
 * port number and sets up the socket.
 *
 * @param server The server structure to initialize.
 * @param port The port number to set.
 * @return bool True on success, false on failure.
 */
static bool init_server(server_t *server, int port)
{
    server->sockfd = setup_socket_fd();
    if (server->sockfd == -1)
        return false;
    server->addr = init_sockin(port);
    if (bind_socket(server->sockfd, &server->addr) == -1)
        return false;
    server->port = set_final_port(server->sockfd);
    return (listen_socket(server->sockfd) != -1);
}

/**
 * @brief Initialize the clients array in the server structure.
 *
 * This function initializes the clients array in the server structure
 * by setting the client socket file descriptors to -1 and other fields
 * to their default values.
 *
 * @param server The server structure to initialize.
 */
static void init_clients(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        server->clients[i].client_sockfd = -1;
        server->clients[i].server = NULL;
        server->clients[i].client_addr = NULL;
        server->clients[i].handshake = HANDSHAKE_DONE;
        server->clients[i].ready = false;
        server->clients[i].flying = false;
    }
}

/**
 * @brief Set up the server socket and initialize the server structure.
 *
 * This function sets up the server socket, initializes the server
 * structure, and prepares it for accepting client connections.
 *
 * @param port The port number to bind the server to.
 * @param debug Boolean value indicating whether to enable debug mode.
 * @return server_t* Pointer to the initialized server structure, or NULL on
 * failure.
 */
server_t *setup_socket(int port, bool debug)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server || !init_server(server, port)) {
        free(server);
        return NULL;
    }
    init_clients(server);
    server->map = NULL;
    server->debug = debug;
    server->next_id = 1;
    server->game_state = GAME_START;
    return server;
}
