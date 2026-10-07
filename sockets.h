#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define K_TYPE_WINDOWS

#include <winsock2.h>
#include <ws2tcpip.h> // Good to include for modern IP lookups

#elif defined(__linux__)

#define K_TYPE_LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#else

#error "Unsupported platform"

#endif


#ifdef K_TYPE_WINDOWS

#define K_SOCKET_TYPE SOCKET
#define K_SOCKET_INVALID INVALID_SOCKET
#define K_SOCKET_ERROR SOCKET_ERROR
#define K_SOCKLEN_TYPE int          /* Windows explicitly uses int for lengths */

#elif defined(K_TYPE_LINUX)

#define K_SOCKET_TYPE int
#define K_SOCKET_INVALID -1
#define K_SOCKET_ERROR -1
#define K_SOCKLEN_TYPE socklen_t    /* POSIX strictly uses socklen_t */

#endif


#ifdef K_TYPE_WINDOWS

#define K_SHUT_RD   SD_RECEIVE
#define K_SHUT_WR   SD_SEND
#define K_SHUT_RDWR SD_BOTH

#elif defined(K_TYPE_LINUX)

#define K_SHUT_RD   SHUT_RD
#define K_SHUT_WR   SHUT_WR
#define K_SHUT_RDWR SHUT_RDWR

#endif


/* Function declarations */
int k_socket_init(void);
void k_socket_cleanup(void);

K_SOCKET_TYPE k_socket_create(int domain, int type, int protocol);

int k_socket_close(K_SOCKET_TYPE sock);
int k_socket_get_last_error(void);
int k_socket_shutdown(K_SOCKET_TYPE sock, int how);
int k_socket_listen(K_SOCKET_TYPE sock, int backlog);

K_SOCKET_TYPE k_socket_accept(
    K_SOCKET_TYPE sock,
    struct sockaddr *addr,
    K_SOCKLEN_TYPE *addrlen
);

int k_socket_connect(
    K_SOCKET_TYPE sock,
    const struct sockaddr *addr,
    K_SOCKLEN_TYPE addrlen
);

int k_socket_send(
    K_SOCKET_TYPE sock,
    const void *buf,
    int len,
    int flags
);

int k_socket_recv(
    K_SOCKET_TYPE sock,
    void *buf,
    int len,
    int flags
);

int k_socket_bind(
    K_SOCKET_TYPE sock,
    const struct sockaddr *addr,
    K_SOCKLEN_TYPE addrlen
);

int k_socket_sendto(
    K_SOCKET_TYPE sock,
    const void *buf,
    int len,
    int flags,
    const struct sockaddr *to,
    K_SOCKLEN_TYPE tolen
);

int k_socket_recvfrom(
    K_SOCKET_TYPE sock,
    void *buf,
    int len,
    int flags,
    struct sockaddr *from,
    K_SOCKLEN_TYPE *fromlen
);

int k_socket_setsockopt(
    K_SOCKET_TYPE sock,
    int level,
    int optname,
    const void *optval,
    K_SOCKLEN_TYPE optlen
);

int k_socket_getsockopt(
    K_SOCKET_TYPE sock,
    int level,
    int optname,
    void *optval,
    K_SOCKLEN_TYPE *optlen
);

int k_socket_get_name(
    K_SOCKET_TYPE sock,
    struct sockaddr *addr,
    K_SOCKLEN_TYPE *addrlen
);
int k_send_all(K_SOCKET_TYPE s, const char *data, int length);