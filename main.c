#include <stdio.h>
#include <string.h>

#include "sockets.h"
#define PORT 8000


K_SOCKET_TYPE sock = K_SOCKET_INVALID;
K_SOCKET_TYPE client_sock = K_SOCKET_INVALID;
int result = 0;
int main(void) {
    if (k_socket_init() == K_SOCKET_ERROR) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 1;
        goto cleanup;
    }
    sock = k_socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == K_SOCKET_INVALID) {
        printf("Failed to create socket\n");
        result = 1;
        goto cleanup;
    }
    struct sockaddr_in server = {};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);
    // Set Socket Option to allow reuse of ports (Needed for repeat runs)
    int opt = 1;
    if (k_socket_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 6;
        goto cleanup;
    }
    if (k_socket_bind(sock, (const struct sockaddr *)&server, sizeof(server)) == K_SOCKET_ERROR) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 2;
        goto cleanup;
    }

    // Define address of client that is trying to connect to socket
    struct sockaddr_in client = {};
    socklen_t client_len = sizeof(client);
    // Accept Client connections
    int listen_result = k_socket_listen(sock, 3);
    if (listen_result == K_SOCKET_ERROR) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 6;
        goto cleanup;
    }
    client_sock = k_socket_accept(sock, (struct sockaddr *)&client, &client_len);
    if (client_sock == K_SOCKET_INVALID) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 3;
        goto cleanup;
    }

    printf("Connected to client\n");
    char buf[1025];
    int bytes_recv = k_socket_recv(client_sock, buf, sizeof(buf) - 1, 0);
    if (bytes_recv < 0) {
        printf("Failed Error #%d", k_socket_get_last_error());
        result = 4;
        goto cleanup;
    }
    printf("Received %d bytes\n", bytes_recv);
    printf("Sending Message BACK\n");
    char message[] = "Hello From Server!";
    int message_len = sizeof(message) - 1;
    int was_sent = k_send_all(client_sock, message, message_len);
    if (was_sent != 0) {
        printf("Failed Error #%d\n", k_socket_get_last_error());
        result = 5;
        goto cleanup;
    }
    printf("Sent %d bytes\n", message_len);


    cleanup:
        if (client_sock != K_SOCKET_INVALID) {
            k_socket_close(client_sock);
        }
        if (sock != K_SOCKET_INVALID) {
            k_socket_close(sock);
        }
        k_socket_cleanup();
        return result;


    return 0;
}