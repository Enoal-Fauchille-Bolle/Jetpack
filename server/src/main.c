/*
** EPITECH PROJECT, 2025
** Jetpack
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define PORT 8050
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct {
    int fd;
    int id;
} Client;

// Remove a client from the pollfd and clients arrays.
// 'index' is the index in the fds array (>= 1) to remove.
void remove_client(struct pollfd fds[], Client clients[], int *client_count, int index) {
    close(fds[index].fd);
    // Shift pollfd array: index 0 is the server, so clients are at indices 1 .. client_count.
    for (int k = index; k < *client_count; k++) {
        fds[k] = fds[k + 1];
    }
    // Shift clients array: clients[0] corresponds to fds[1]
    for (int k = index - 1; k < *client_count - 1; k++) {
        clients[k] = clients[k + 1];
    }
    (*client_count)--;
}

int main() {
    int server_fd, next_id = 0;
    struct sockaddr_in server_addr;
    // We need one extra slot for the server fd at index 0.
    struct pollfd fds[MAX_CLIENTS + 1];
    Client clients[MAX_CLIENTS];
    int client_count = 0;

    // Create server socket.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Allow immediate reuse of the port after exit.
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Setup address.
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind.
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen.
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    fds[0].fd = server_fd;
    fds[0].events = POLLIN;

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        int nfds = client_count + 1; // server + clients
        int poll_count = poll(fds, nfds, -1);
        if (poll_count < 0) {
            perror("poll");
            break;
        }

        if (fds[0].revents & POLLIN) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
            if (client_fd < 0) {
                perror("accept");
            } else {
                if (client_count >= MAX_CLIENTS) {
                    printf("Max clients reached, rejecting connection...\n");
                    close(client_fd);
                } else {
                    clients[client_count].fd = client_fd;
                    clients[client_count].id = next_id++;
                    fds[client_count + 1].fd = client_fd;
                    fds[client_count + 1].events = POLLIN;
                    client_count++;

                    char welcome_msg[BUFFER_SIZE];
                    snprintf(welcome_msg, sizeof(welcome_msg), "ID %d\n", clients[client_count - 1].id);
                    send(client_fd, welcome_msg, strlen(welcome_msg), 0);
                    printf("New client connected, assigned ID %d\n", clients[client_count - 1].id);
                }
            }
        }

        // Check for data on each client socket.
        for (int i = 1; i <= client_count; i++) {
            if (fds[i].revents & POLLIN) {
                char buffer[BUFFER_SIZE] = {0};
                int bytes_read = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);
                if (bytes_read <= 0) {
                    // Connection closed or error.
                    printf("Client %d disconnected.\n", clients[i - 1].id);
                    remove_client(fds, clients, &client_count, i);
                    i--; // Adjust index after removal.
                    continue;
                }

                buffer[bytes_read] = '\0';
                printf("Received from client %d: %s", clients[i - 1].id, buffer);

                char message[BUFFER_SIZE];
                snprintf(message, sizeof(message), "data from client %d: %.1000s", clients[i - 1].id, buffer);

                for (int j = 1; j <= client_count; j++) {
                    if (fds[j].fd != fds[i].fd) {
                        send(fds[j].fd, message, strlen(message), 0);
                    }
                }
            }
        }
    }

    // Cleanup.
    for (int i = 0; i <= client_count; i++) {
        close(fds[i].fd);
    }
    return 0;
}
