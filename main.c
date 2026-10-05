#include <stdio.h>
#include "sockets.h"

int main(void) {
    if (k_socket_init() == K_SOCKET_ERROR)
        return 1;

    K_SOCKET_TYPE sock = k_socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock == K_SOCKET_INVALID)
        return 1;

    struct sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    if (k_socket_bind(sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) == K_SOCKET_ERROR)
        return 1;

    if (k_socket_listen(sock, 3) == K_SOCKET_ERROR)
        return 1;

    printf("Listening on port 8080\n");
    socklen_t serv_size = sizeof(serv_addr);
    struct sockaddr_in client_addr = {};
    K_SOCKLEN_TYPE client_size = sizeof(client_addr);

    K_SOCKET_TYPE client = k_socket_accept(
        sock,
        (struct sockaddr *)&client_addr,
        &client_size
    );
    if (client == K_SOCKET_INVALID)
        return 1;


    k_socket_close(sock);
    k_socket_close(client);
    k_socket_cleanup();

    return 0;
}