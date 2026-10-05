#include "sockets.h"


int k_socket_init(void)
{
#ifdef K_TYPE_WINDOWS

    WSADATA wsaData;

    return WSAStartup(
        MAKEWORD(2, 2),
        &wsaData
    ) == 0 ? 0 : K_SOCKET_ERROR;

#elif defined(K_TYPE_LINUX)

    /* No initialization required on Linux. */
    return 0;

#endif
}


void k_socket_cleanup(void)
{
#ifdef K_TYPE_WINDOWS

    WSACleanup();

#elif defined(K_TYPE_LINUX)

    /* No cleanup required on Linux. */

#endif
}


K_SOCKET_TYPE k_socket_create(
    int domain,
    int type,
    int protocol)
{
    return socket(
        domain,
        type,
        protocol
    );
}


int k_socket_close(K_SOCKET_TYPE sock)
{
#ifdef K_TYPE_WINDOWS

    return closesocket(sock);

#elif defined(K_TYPE_LINUX)

    return close(sock);

#endif
}


int k_socket_get_last_error(void)
{
#ifdef K_TYPE_WINDOWS

    return WSAGetLastError();

#elif defined(K_TYPE_LINUX)

    return errno;

#endif
}


int k_socket_shutdown(
    K_SOCKET_TYPE sock,
    int how)
{
    return shutdown(
        sock,
        how
    ) == 0 ? 0 : K_SOCKET_ERROR;
}


int k_socket_listen(
    K_SOCKET_TYPE sock,
    int backlog)
{
    return listen(
        sock,
        backlog
    ) == 0 ? 0 : K_SOCKET_ERROR;
}


K_SOCKET_TYPE k_socket_accept(
    K_SOCKET_TYPE sock,
    struct sockaddr *addr,
    K_SOCKLEN_TYPE *addrlen)
{
#ifdef K_TYPE_WINDOWS

    return accept(
        sock,
        addr,
        addrlen
    );

#elif defined(K_TYPE_LINUX)

    socklen_t len = (socklen_t)*addrlen;

    K_SOCKET_TYPE client_fd = accept(
        sock,
        addr,
        &len
    );

    *addrlen = (K_SOCKLEN_TYPE)len;

    return client_fd;

#endif
}


int k_socket_connect(
    K_SOCKET_TYPE sock,
    const struct sockaddr *addr,
    K_SOCKLEN_TYPE addrlen)
{
    return connect(
        sock,
        addr,
        addrlen
    ) == 0 ? 0 : K_SOCKET_ERROR;
}


int k_socket_bind(
    K_SOCKET_TYPE sock,
    const struct sockaddr *addr,
    K_SOCKLEN_TYPE addrlen)
{
    return bind(
        sock,
        addr,
        addrlen
    ) == 0 ? 0 : K_SOCKET_ERROR;
}


int k_socket_send(
    K_SOCKET_TYPE sock,
    const void *buf,
    int len,
    int flags)
{
    return send(
        sock,
        buf,
        len,
        flags
    );
}


int k_socket_recv(
    K_SOCKET_TYPE sock,
    void *buf,
    int len,
    int flags)
{
    return recv(
        sock,
        buf,
        len,
        flags
    );
}


int k_socket_sendto(
    K_SOCKET_TYPE sock,
    const void *buf,
    int len,
    int flags,
    const struct sockaddr *to,
    K_SOCKLEN_TYPE tolen)
{
    return sendto(
        sock,
        buf,
        len,
        flags,
        to,
        tolen
    );
}


int k_socket_recvfrom(
    K_SOCKET_TYPE sock,
    void *buf,
    int len,
    int flags,
    struct sockaddr *from,
    K_SOCKLEN_TYPE *fromlen)
{
#ifdef K_TYPE_WINDOWS

    return recvfrom(
        sock,
        buf,
        len,
        flags,
        from,
        fromlen
    );

#elif defined(K_TYPE_LINUX)

    socklen_t addr_len = (socklen_t)*fromlen;

    int ret = recvfrom(
        sock,
        buf,
        len,
        flags,
        from,
        &addr_len
    );

    *fromlen = (K_SOCKLEN_TYPE)addr_len;

    return ret;

#endif
}


int k_socket_setsockopt(
    K_SOCKET_TYPE sock,
    int level,
    int optname,
    const void *optval,
    K_SOCKLEN_TYPE optlen)
{
#ifdef K_TYPE_WINDOWS

    return setsockopt(
        sock,
        level,
        optname,
        optval,
        optlen
    ) == 0 ? 0 : K_SOCKET_ERROR;

#elif defined(K_TYPE_LINUX)

    return setsockopt(
        sock,
        level,
        optname,
        optval,
        optlen
    ) == 0 ? 0 : K_SOCKET_ERROR;

#endif
}


int k_socket_getsockopt(
    K_SOCKET_TYPE sock,
    int level,
    int optname,
    void *optval,
    K_SOCKLEN_TYPE *optlen)
{
#ifdef K_TYPE_WINDOWS

    return getsockopt(
        sock,
        level,
        optname,
        optval,
        optlen
    ) == 0 ? 0 : K_SOCKET_ERROR;

#elif defined(K_TYPE_LINUX)

    socklen_t options_len = (socklen_t)*optlen;

    int ret = getsockopt(
        sock,
        level,
        optname,
        optval,
        &options_len
    );

    *optlen = (K_SOCKLEN_TYPE)options_len;

    return ret == 0 ? 0 : K_SOCKET_ERROR;

#endif
}


int k_socket_get_name(
    K_SOCKET_TYPE sock,
    struct sockaddr *addr,
    K_SOCKLEN_TYPE *addrlen)
{
#ifdef K_TYPE_WINDOWS

    return getsockname(
        sock,
        addr,
        addrlen
    ) == 0 ? 0 : K_SOCKET_ERROR;

#elif defined(K_TYPE_LINUX)

    socklen_t len = (socklen_t)*addrlen;

    int ret = getsockname(
        sock,
        addr,
        &len
    );

    *addrlen = (K_SOCKLEN_TYPE)len;

    return ret == 0 ? 0 : K_SOCKET_ERROR;

#endif
}
