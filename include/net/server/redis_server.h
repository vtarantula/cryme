#ifndef REDIS_SERVER_H__
#define REDIS_SERVER_H__

// C++ Headers
#include <string.h>
#include <unistd.h>
#include <stdexcept>

// Network headers
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

// Application Headers


void work(const int* conn_fd)
{
    // Do the work for the client
    char rbuf[64] = {};
    ssize_t n = read(*conn_fd, rbuf, sizeof(rbuf) - 1);
    if (n < 0)
    {
        printf("read() error; size: %li\n", n);
        return;
    }
    printf("Client: %s\n", rbuf);

    char wbuf[] = "world";
    write(*conn_fd, wbuf, strlen(wbuf));
    return;
}

void server_listen(const int* port)
{
    printf("Starting server:\n");
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(*port);
    addr.sin_addr.s_addr = ntohl(0);    // Bind to 0.0.0.0

    int rv = bind(fd, (const sockaddr*) &addr, sizeof(addr));
    if (rv)
    {
        throw std::runtime_error("Unable to bind()");
    }

    rv = listen(fd, SOMAXCONN);
    if (rv)
    {
        throw std::runtime_error("Unable to listen()");
    }

    while (true)
    {
        struct sockaddr_in client_addr = {};
        socklen_t socklen = sizeof(client_addr);

        int conn_fd = accept(fd, (struct sockaddr*)&client_addr, &socklen);
        if (conn_fd < 0)
        {
            continue;
        }
        // Do some work with the connection
        work(&conn_fd);
        close(conn_fd);
    }
    return;
}


#endif    // REDIS_SERVER_H__